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
	void setColor( sf::Color color_ );

	const std::string& getString() const;
	const BitmapFont* getFont() const;
	sf::Color getColor() const;

	RectF getLocalBounds() const;
	RectF getGlobalBounds() const;

	void draw( sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	inline static constexpr size_t TAB_WIDTH = 4; // In characters
	std::string string;
	const BitmapFont* font = nullptr;
	sf::Color color = sf::Color::White;
	sf::VertexArray vertices{ sf::Quads };

	void update();
};
}