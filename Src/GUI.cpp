/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/GUI.hpp"
#include "Engine/Input.hpp"

namespace con::priv
{
GUIClass::GUIClass()
{
	setTarget( Global.GameWindow );
}

void GUIClass::render( sf::RenderWindow& window )
{
	draw();
}
}
