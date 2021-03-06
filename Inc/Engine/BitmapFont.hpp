/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

/*
Based on code by @dabbertorres:
https://github.com/dabbertorres/sfml-bitmap-text
*/

#pragma once

namespace con
{
// Remeber to call setGlyphSize!
// Handles glyps from space above.
class BitmapFont final
{
public:
	bool loadFromFile( const std::string& path );

	// @hack - it has to be const to fit into BasicAssetsHolder. 
	void setGlyphSize( const Vec2i& size ) const;

	const sf::Texture& getTexture() const;
	Vec2i getGlyphSize() const;
	Vec2i getGlyph( uint32_t codePoint ) const;

private:
	sf::Texture texture;
	mutable Vec2i glyphSize{ -1, -1 };
};
}