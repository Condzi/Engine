/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"
#include "Engine/BitmapFont.hpp"
#include "Engine/Debug.hpp"

namespace con
{
bool con::BitmapFont::loadFromFile( const std::string& path )
{
	return texture.loadFromFile( path );
}

void BitmapFont::setGlyphSize( const Vec2i& size ) const
{
	glyphSize = size;
}

const sf::Texture& BitmapFont::getTexture() const
{
	return texture;
}

Vec2i BitmapFont::getGlyphSize() const
{
	return glyphSize;
}

Vec2i BitmapFont::getGlyph( uint32_t codePoint ) const
{
	if ( texture.getSize() == Vec2u{ 0,0 } ) {
		Global.Logger.print( con::LogPriority::Error, "BitmapFont isn't loaded." );
		DebugBreak();
		return { 0,0 };
	}
	if ( glyphSize.x < 0 || glyphSize.y < 0 ) {
		Global.Logger.print( con::LogPriority::Error, "Glyph size is not set in bitmap font!" );
		DebugBreak();
		return { 0,0 };
	}

	const auto textureSize = texture.getSize();
	const auto cols = textureSize.x / glyphSize.x;
	const auto rows = textureSize.y / glyphSize.y;

	if ( codePoint < cols * rows )
		return Vec2i( glyphSize.x * ( codePoint % cols ), glyphSize.y * ( codePoint / cols ) );
	else {
		Global.Logger.print( con::LogPriority::Error, "Unable to find glyph (%).", codePoint );
		DebugBreak();
		return { 0,0 };
	}
}
}
