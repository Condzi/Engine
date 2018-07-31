/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

/*
Based on code by @dabbertorres:
https://github.com/dabbertorres/sfml-bitmap-text
*/

#pragma once

#include "Engine/Drawable.hpp"
#include "Engine/BitmapFont.hpp"

namespace con
{
class BitmapText final :
	public sf::Transformable,
	public sf::Drawable
{
public:
	BitmapText() = default;
	BitmapText( const std::string& string_, const BitmapFont& font_, const Vec2f& pos = {}, sf::Color color_ = sf::Color::White );

	void setString( const std::string& string_ );
	void setFont( const BitmapFont& font_ );
	void setColor( sf::Color color, size_t idx, size_t count = 1 );
	void setColors( sf::Color color );

	const std::string& getString() const;
	const BitmapFont* getFont() const;
	sf::Color getColor( size_t index ) const;
	const std::vector<sf::Color>& getColors() const;

	RectF getLocalBounds() const;
	RectF getGlobalBounds() const;

	void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
	inline static constexpr size_t TAB_WIDTH = 4; // In characters
	std::string string;
	const BitmapFont* font = nullptr;
	std::vector<sf::Color> colors;
	sf::VertexArray vertices{ sf::Quads };

	void update();
};
}