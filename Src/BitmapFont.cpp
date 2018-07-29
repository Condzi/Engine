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

void BitmapFont::setGlyphSize( const Vec2i& size )
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
	if ( glyphSize.x < 0 || glyphSize.y < 0 ) {
		Global.Logger.log( con::LogPriority::Error, "Glyph size is not set in bitmap font!" );
		DebugBreak();
		return { 0,0 };
	}

	const auto textureSize = texture.getSize();
	const auto cols = textureSize.x / glyphSize.x;
	const auto rows = textureSize.y / glyphSize.y;

	// cancel out control characters
	// codePoint -= 32;

	if ( codePoint < cols * rows )
		return Vec2i( glyphSize.x * ( codePoint % cols ), glyphSize.y * ( codePoint / cols ) );
	else {
		Global.Logger.log( con::LogPriority::Error, "Unable to find glyph (", codePoint, ")." );
		DebugBreak();
		return { 0,0 };
	}
}
}
