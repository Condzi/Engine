/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"
#include "Engine/BitmapText.hpp"

namespace con
{
BitmapText::BitmapText( const std::string& string_, const BitmapFont& font_, const Vec2f& pos, sf::Color color_ ) :
	string( string_ ),
	font( &font_ )
{
	setPosition( pos );
	update();
}

void BitmapText::setString( const std::string& string_ )
{
	string = string_;
	update();
}

void BitmapText::setFont( const BitmapFont& font_ )
{
	font = &font_;
	update();
}

void BitmapText::setColor( sf::Color color, size_t idx, size_t count )
{
	std::fill( colors.begin() + idx, colors.begin() + idx + count, color );
	update();
}

void BitmapText::setColors( sf::Color color )
{
	std::fill( colors.begin(), colors.end(), color );
	update();
}

const std::string& BitmapText::getString() const
{
	return string;
}

const BitmapFont * BitmapText::getFont() const
{
	return font;
}

sf::Color BitmapText::getColor( size_t index ) const
{
	return colors.at( index );
}

const std::vector<sf::Color>& BitmapText::getColors() const
{
	return colors;
}

RectF BitmapText::getLocalBounds() const
{
	if ( !font )
		return{};

	size_t idx{}, numLines{}, longestLine{};

	const auto strSize = string.size();

	while ( idx != std::string::npos && idx < strSize ) {
		std::size_t next = std::min( string.find( '\n', idx ), strSize );

		auto tabs = std::count( string.begin() + idx, string.begin() + next, '\t' );

		auto len = next - idx + tabs * ( TAB_WIDTH - 1 );	// "next - idx" already counts each tab once

		longestLine = std::max( longestLine, len );

		idx = next + 1;
		++numLines;
	}

	auto size = font->getGlyphSize();
	return{ 0, 0, static_cast<float32_t>( longestLine * size.x ), static_cast<float32_t>( numLines * size.y ) };
}

RectF BitmapText::getGlobalBounds() const
{
	return getTransform().transformRect( getLocalBounds() );
}

void BitmapText::draw( sf::RenderTarget & target, sf::RenderStates states ) const
{
	if ( !font )
		return;

	states.transform *= getTransform();
	states.texture = &font->getTexture();
	target.draw( vertices, states );
}

void BitmapText::update()
{
	colors.resize( string.size(), sf::Color::White );

	if ( !font )
		return;

	vertices.clear();

	// count number of spacing characters to remove from total string length,
	// for pre-calculating number of vertices needed
	const auto spaceChars = std::count_if( string.begin(), string.end(), []( auto c ) { return c == ' ' || c == '\n' || c == '\t'; } );

	const auto strSize = string.size();
	const auto drawableChars = strSize - spaceChars;

	vertices.resize( drawableChars * 4 );	// 4 verts per character

	const auto glyphSize = static_cast<sf::Vector2f>( font->getGlyphSize() );
	Vec2f pos;

	auto vertIdx = 0u;
	for ( auto i = 0u; i < strSize; ++i ) {
		auto c = string[i];

		switch ( c ) {
		case ' ':
			pos.x += glyphSize.x;
			continue;

		case '\t':
			pos.x += glyphSize.x * TAB_WIDTH;
			continue;

		case '\n':
			pos.x = 0;
			pos.y += glyphSize.y;
			continue;

		default:
		{
			auto* vert = &vertices[vertIdx * 4];
			auto color = colors.at( i );

			auto texCoord = static_cast<Vec2f>( font->getGlyph( c ) );

			// top left
			vert->color = color;
			vert->position = pos;
			vert->texCoords = texCoord;
			++vert;

			// top right
			vert->color = color;
			vert->position = pos + sf::Vector2f{ glyphSize.x, 0 };
			vert->texCoords = texCoord + sf::Vector2f{ glyphSize.x, 0 };
			++vert;

			// bot right
			vert->color = color;
			vert->position = pos + glyphSize;
			vert->texCoords = texCoord + glyphSize;
			++vert;

			// bot left
			vert->color = color;
			vert->position = pos + sf::Vector2f{ 0, glyphSize.y };
			vert->texCoords = texCoord + sf::Vector2f{ 0, glyphSize.y };

			// next character
			pos.x += glyphSize.x;

			++vertIdx;
			break;
		}
		}
	}
}
}