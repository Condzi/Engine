/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Input.hpp"
#include "Engine/GUI.hpp"

namespace con::priv
{
bool InputClass::isUp( KeyboardKey key ) const
{
	return keyboardKeys.at( key ) == KeyState::Up && Global.GameWindow.hasFocus();
}

bool InputClass::isDown( KeyboardKey key ) const
{
	return keyboardKeys.at( key ) == KeyState::Down && Global.GameWindow.hasFocus();
}

bool InputClass::isHeld( KeyboardKey key ) const
{
	return sf::Keyboard::isKeyPressed( key ) && Global.GameWindow.hasFocus();
}

bool InputClass::isUp( MouseButton button ) const
{
	return mouseButtons.at( button ) == KeyState::Up && Global.GameWindow.hasFocus();
}

bool InputClass::isDown( MouseButton button ) const
{
	return mouseButtons.at( button ) == KeyState::Down && Global.GameWindow.hasFocus();
}

bool InputClass::isHeld( MouseButton button ) const
{
	return sf::Mouse::isButtonPressed( button ) && Global.GameWindow.hasFocus();
}

Vec2i InputClass::getMousePosition() const
{
	return sf::Mouse::getPosition( Global.GameWindow );
}

bool InputClass::doesMouseMoved() const
{
	return mouseMoved;
}

void InputClass::_dispatchEvents()
{
	using EventType = sf::Event::EventType;

	mouseMoved = false;
	clearStates();

	sf::Event event;
	while ( Global.GameWindow.pollEvent( event ) ) {
		switch ( event.type ) {
		case EventType::Closed:
		{
			Global.ExitGame = true;
			break;
		}
		case EventType::KeyReleased:
		{
			keyboardKeys.at( event.key.code ) = KeyState::Up;
			break;
		}
		case EventType::KeyPressed:
		{
			keyboardKeys.at( event.key.code ) = KeyState::Down;
			break;
		}
		case EventType::MouseButtonReleased:
		{
			mouseButtons.at( event.mouseButton.button ) = KeyState::Up;
			break;
		}
		case EventType::MouseButtonPressed:
		{
			mouseButtons.at( event.mouseButton.button ) = KeyState::Down;
			break;
		}
		case EventType::MouseMoved:
		{
			mouseMoved = true;
			break;
		}
		case EventType::Resized:
		{
			auto width = ConvertTo<float32_t>( event.size.width );
			auto height = ConvertTo<float32_t>( event.size.height );

			sf::View updatedView( RectF( 0, 0, width, height ) );
			Global.GameWindow.setView( updatedView );
			Global.GUI.setView( updatedView );
			break;
		}
		}

		Global.GUI.handleEvent( event );
	}
}

void InputClass::clearStates()
{
	mouseMoved = false;
	keyboardKeys.fill( KeyState::None );
	mouseButtons.fill( KeyState::None );
}
}