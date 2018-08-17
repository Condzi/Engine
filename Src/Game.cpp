/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Game.hpp"
#include "Engine/Updater.hpp"
#include "Engine/Input.hpp"
#include "Engine/Assets.hpp"
#include "Engine/GUI.hpp"

namespace con::priv
{
void GameClass::run()
{
	if ( !loadSettings() || !validateSettings() )
		makeDefaultSettings();

	configureFromSettings();

	sf::Clock fpsClock;
	while ( !Global.ExitGame ) {
		Global.Input._dispatchEvents();
		Global._Updater.update();

		Global.FrameTime = fpsClock.restart();
	}
}

bool GameClass::loadSettings()
{
	return Global.Assets.Settings.load( "settings.ini" );
}

bool GameClass::validateSettings()
{
	auto& settings = Global.Assets.Settings;

	if ( !settings.getValue( "WINDOW", "WIDTH" ).has_value() )
		print( LogPriority::Error, "Missing % setting.", "WINDOW WIDTH" );
	else if ( !settings.getValue( "WINDOW", "HEIGHT" ).has_value() )
		print( LogPriority::Error, "Missing % setting.", "WINDOW HEIHT" );
	else if ( !settings.getValue( "WINDOW", "FPS" ).has_value() )
		print( LogPriority::Error, "Missing % setting.", "WINDOW FPS" );
	else
		return true;

	return false;
}

void GameClass::makeDefaultSettings()
{
	auto& settings = Global.Assets.Settings;

	settings.setValue( "WINDOW", "WIDTH", "1280" );
	settings.setValue( "WINDOW", "HEIGHT", "720" );
	settings.setValue( "WINDOW", "FPS", "60" );
}

void GameClass::configureFromSettings()
{
	auto& settings = Global.Assets.Settings;

	auto winWidth = ConvertTo<uint32_t>( settings.getValue( "WINDOW", "WIDTH" ).value() );
	auto winHeight = ConvertTo<uint32_t>( settings.getValue( "WINDOW", "HEIGHT" ).value() );
	auto fps = ConvertTo<uint32_t>( settings.getValue( "WINDOW", "FPS" ).value() );

	Global.GameWindow.create( { winWidth, winHeight }, "game", sf::Style::Close );
	Global.GUI.setView( Global.GameWindow.getView() );
	Global.GUI.setDrawLayer( std::numeric_limits<int16_t>::max() );
	Global.GameWindow.setFramerateLimit( fps );
}
}