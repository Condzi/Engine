/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/Utility.hpp"
#include "Engine/IUpdatable.hpp"
#include "Engine/Entity.hpp"

namespace con
{
class IDrawable
{
public:
	bool AffectedByView = true;

	IDrawable();
	RULE_OF_FIVE_NO_CTOR( IDrawable );
	virtual ~IDrawable();

	void setDrawLayer( int16_t layer_ );
	int16_t getDrawLayer() const;
	// @ToDo: Probably useless.
	void boundWithEntity( Entity* boundedEntity_ );
	Entity* getBoundedEntity() const;
	bool isBoundedWithEntity() const;

	virtual void render( sf::RenderWindow& window ) {}

protected:
	Entity* boundedEntity = nullptr;
	int16_t layer = 0;

	template <typename TDrawable>
	void renderInternal( sf::RenderWindow& window, TDrawable& drawable )
	{
		static_assert( std::is_base_of_v<sf::Drawable, TDrawable> );

		if ( !AffectedByView ) {
			auto org = window.getView();
			window.setView( window.getDefaultView() );
			window.draw( drawable );
			window.setView( org );
		} else
			window.draw( drawable );
	}
};

struct AnimationInfo final
{
	const sf::Texture* sheet = nullptr;
	Vec2u frameSize;
	uint16_t begin = 0;
	uint16_t framesCount = 0;
	uint16_t fps = 0;
};

class IAnimation :
	public IDrawable,
	public IUpdatable,
	public ILogger
{
public:
	bool isAnimation = false;
	AnimationInfo animationInfo;

	int8_t getUpdatePriority() const
	{
		return UpdatePriority::Drawable;
	}

protected:
	void updateFrameTime();
	std::optional<sf::IntRect> getFrameRect();

private:
	sf::Time currentFrameTime;
	uint16_t currentFrameNumber = 0;

	bool errorWithInfo();

	std::string loggerName() const override
	{
		return "IAnimation";
	}
};

class RectangleShape :
	public sf::RectangleShape,
	public IAnimation
{
public:
	using sf::RectangleShape::RectangleShape;

	void render( sf::RenderWindow& window ) override;

private:
	void update() override;
};

class CircleShape :
	public sf::CircleShape,
	public IAnimation
{
public:
	using sf::CircleShape::CircleShape;

	void render( sf::RenderWindow& window ) override;

private:
	void update() override;
};

class Sprite :
	public sf::Sprite,
	public IAnimation
{
public:
	using sf::Sprite::Sprite;

	void render( sf::RenderWindow& window ) override;

private:
	void update() override;
};

class Text :
	public sf::Text,
	public IDrawable
{
public:
	using sf::Text::Text;

	void render( sf::RenderWindow& window ) override;
};
}