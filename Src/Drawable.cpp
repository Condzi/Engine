/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Drawable.hpp"
#include "Engine/Renderer.hpp"

namespace con
{
IDrawable::IDrawable()
{
	Global._Renderer.add( this );
}
IDrawable::~IDrawable()
{
	Global._Renderer.remove( this );
}

void IDrawable::setDrawLayer( int16_t layer_ )
{
	layer = layer_;
}

int16_t IDrawable::getDrawLayer() const
{
	return layer;
}

void IDrawable::boundWithEntity( Entity* boundedEntity_ )
{
	boundedEntity = boundedEntity_;
}

Entity* IDrawable::getBoundedEntity() const
{
	return boundedEntity;
}

bool IDrawable::isBoundedWithEntity() const
{
	return boundedEntity != nullptr;
}

void RectangleShape::render( sf::RenderWindow& window )
{
	renderInternal( window, *this );
}

void RectangleShape::update()
{
	updateFrameTime();
	if ( auto opt = getFrameRect(); opt.has_value() ) {
		setTexture( animationInfo.sheet );
		setTextureRect( opt.value() );
	}
}

void CircleShape::render( sf::RenderWindow& window )
{
	renderInternal( window, *this );
}

void CircleShape::update()
{
	updateFrameTime();
	if ( auto opt = getFrameRect(); opt.has_value() ) {
		setTexture( animationInfo.sheet );
		setTextureRect( opt.value() );
	}
}

void Sprite::render( sf::RenderWindow& window )
{
	renderInternal( window, *this );
}

void Sprite::update()
{
	updateFrameTime();
	if ( auto opt = getFrameRect(); opt.has_value() ) {
		// Incosistency - rest of drawables need pointer, Sprite needs a reference. 
		setTexture( *animationInfo.sheet );
		setTextureRect( opt.value() );
	}
}

void Text::render( sf::RenderWindow& window )
{
	renderInternal( window, *this );
}

void IAnimation::updateFrameTime()
{
	const auto& ai = animationInfo;

	if ( !isAnimation )
		return;

	if ( errorWithInfo() ) {
		isAnimation = false;
		return;
	}

	currentFrameTime += Global.FrameTime;
	const sf::Time fps = sf::seconds( 1.f / ai.fps );
	if ( currentFrameTime > fps ) {
		currentFrameTime -= fps;

		if ( ++currentFrameNumber == ai.framesCount )
			currentFrameNumber = 0;
	}
}
std::optional<sf::IntRect> IAnimation::getFrameRect()
{
	const auto& ai = animationInfo;

	if ( !isAnimation )
		return {};

	auto newFrameXpos = ( currentFrameNumber + ai.begin ) * ai.frameSize.x;
	return sf::IntRect( newFrameXpos, 0, ai.frameSize.x, ai.frameSize.y );
}

bool IAnimation::errorWithInfo()
{
	const auto& ai = animationInfo;

	if ( !ai.sheet ) {
		print( LogPriority::Error, "null sheet." );
	} else if ( ai.sheet->getSize().x < ( ai.framesCount + ai.begin ) * ai.frameSize.x ) {
		auto has = ai.sheet->getSize().x;
		auto need = ai.framesCount * ai.frameSize.x;

		print( LogPriority::Error, "sheet is smaller in X than declared (is %, but % needed).", has, need );
	} else if ( ai.sheet->getSize().y < ai.frameSize.y ) {
		auto has = ai.sheet->getSize().y;
		auto need = ai.frameSize.y;

		print( LogPriority::Error, "sheet is smaller in Y than declared (is %, but % needed).", has, need );
	} else
		return false;

	return true;
}

void BitmapText::render( sf::RenderWindow& window )
{
	renderInternal( window, *this );
}
}