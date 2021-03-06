/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

/*
Based on code by @dabbertorres:
https://github.com/dabbertorres/sfml-bitmap-text
*/

#pragma once

#include "Engine/BitmapFont.hpp"

namespace con::priv
{
// For con::BitmapText see Drawable.hpp
class BitmapText :
	public sf::Transformable,
	public sf::Drawable
{
public:
	BitmapText() = default;
	BitmapText( const std::string& string_, const BitmapFont& font_, const Vec2f& pos = {}, sf::Color color_ = sf::Color::White );

	virtual ~BitmapText() = default;

	void setString( const std::string& string_ );
	void setFont( const BitmapFont& font_ );
	void setColorForIdx( sf::Color color, size_t idx, size_t count = 1 );
	void setDefaultColor( sf::Color color );

	const std::string& getString() const;
	const BitmapFont* getFont() const;
	sf::Color getDefaultColor() const;
	sf::Color getColorAtIdx( size_t index ) const;
	const std::vector<sf::Color>& getLettersColors() const;

	RectF getLocalBounds() const;
	RectF getGlobalBounds() const;

	void draw( sf::RenderTarget& target, sf::RenderStates states ) const override;

private:
	inline static constexpr size_t TAB_WIDTH = 4; // In characters
	std::string string;
	const BitmapFont* font = nullptr;
	sf::Color defaultColor = sf::Color::White;
	std::vector<sf::Color> colors;
	sf::VertexArray vertices{ sf::Quads };

	void update();
};
}