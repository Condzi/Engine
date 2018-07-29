/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include <filesystem>
// for sleep
#include <thread>

#include "Catch.hpp"

#include <Engine/Assets.hpp>
#include <Engine/INIFile.hpp>
#include <Engine/BitmapFont.hpp>

// @For BitmapText
#include "Engine/Renderer.hpp"
#include <Engine/BitmapText.hpp>


TEST_CASE( "INI File Reader (aka Settings)", "[Assets]" )
{
	static constexpr const char* TEST_INI_PATH = "Data/test.ini";

	{
		con::INIFile ini;
		ini.setValue( "SECTION_A", "name1", "val1" );
		ini.setValue( "SECTION_A", "name2", "val2" );
		ini.setValue( "SECTION_A", "name2", "val123" );

		ini.setValue( "SECTION_B", "name1", "val1" );
		ini.setValue( "SECTION_B", "name2", "val2" );

		ini.save( TEST_INI_PATH );
	}

	{
		con::INIFile ini;
		REQUIRE( ini.load( TEST_INI_PATH ) == true );
		REQUIRE( ini.getValue( "SECTION_A", "name1" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_A", "name1" ).value_or( "(err)" ) == "val1" );
		REQUIRE( ini.getValue( "SECTION_A", "name2" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_A", "name2" ).value_or( "(err)" ) == "val123" );

		REQUIRE( ini.getValue( "SECTION_B", "name1" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_B", "name1" ).value_or( "(err)" ) == "val1" );
		REQUIRE( ini.getValue( "SECTION_B", "name2" ).has_value() );
		REQUIRE( ini.getValue( "SECTION_B", "name2" ).value_or( "(err)" ) == "val2" );
		auto sections = ini.getAllSectionsNames();

		REQUIRE( sections.size() == 2 );
		REQUIRE( sections.at( 0 ) == "SECTION_A" );
		REQUIRE( sections.at( 1 ) == "SECTION_B" );
	}

	std::experimental::filesystem::remove( TEST_INI_PATH );
}


TEST_CASE( "Basic Asset Holder (sf::Texture)", "[Assets]" )
{
	static constexpr const char* TEST_IMG_PATH = "Data/test.png";

	{
		sf::Image testImg;
		testImg.create( 32, 32, sf::Color::Green );
		testImg.saveToFile( TEST_IMG_PATH );
	}

	auto& texture = con::Global.Assets.Texture;

	{
		REQUIRE( texture.load( TEST_IMG_PATH, "test" ) == true );
		// green vs red
		REQUIRE( texture.get( "test" ).copyToImage().getPixel( 0, 0 ) != texture.getDefault().copyToImage().getPixel( 0, 0 ) );
	}

	std::experimental::filesystem::remove( TEST_IMG_PATH );
}

TEST_CASE( "IAudioHolder (sf::Sound)", "[Assets]" )
{
	static constexpr const char* TEST_SOUND_PATH = "Data/test.wav";

	auto& sound = con::Global.Assets.Sound;

	REQUIRE( sound.load( TEST_SOUND_PATH, "test" ) == true );
	sound.setVolume( 50 );
	sound.play( "test" );
	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	sound.setVolume( 10 );
	sound.play( "test" );
	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	sound.setVolume( 100 );
	sound.play( "test" );
	sound.setVolume( 0 );
	// to overflow sound palyers in SoundHolder
	for ( size_t i = 0; i < 33; ++i )
		sound.play( "test" );

	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
}

TEST_CASE( "IAudioHolder (sf::Music)", "[Assets]" )
{
	static constexpr const char* TEST_MUSIC_PATH = "Data/test.wav";

	auto& music = con::Global.Assets.Music;

	music.add( TEST_MUSIC_PATH, "test" );
	// doesn't return bool but we can check "isPlaying" to see is it working
	music.play( "test" );
	REQUIRE( music.isPlaying() == true );
}

TEST_CASE( "Bitmap Font", "[Assets]" )
{
	con::BitmapFont font;
	REQUIRE( font.loadFromFile( "data/vincent.png" ) );
	font.setGlyphSize( { 8,8 } );

	auto g = font.getGlyph( 'a' );
	REQUIRE( g.x == 0 );
	REQUIRE( g.y == static_cast<int>( 'a' ) * 8 );

	g = font.getGlyph( 'B' );
	REQUIRE( g.x == 0 );
	REQUIRE( g.y == static_cast<int>( 'B' ) * 8 );
}

// @ToDo: Maybe create 'Visual' file?
TEST_CASE( "Bitmap Text", "[Assets]" )
{
	con::BitmapFont font;
	font.loadFromFile( "data/vincent.png" );
	font.setGlyphSize( { 8,8 } );

	con::BitmapText text( "PRESS SPACE IF YOU CAN SEE ME! \1", font, { 200,200 }, sf::Color::Red );

	auto& gw = con::Global.GameWindow;
	gw.create( { 800,600 }, "" );
	sf::Event ev;

	while ( gw.isOpen() ) {
		while ( gw.pollEvent( ev ) )
			if ( ev.type == sf::Event::KeyPressed ) {
				if ( ev.key.code == sf::Keyboard::Space )
					gw.close();
				else {
					gw.close();
					REQUIRE( false );
				}
			}

		gw.clear();
		text.render( gw );
		gw.display();
	}
}