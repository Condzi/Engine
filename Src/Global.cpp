/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Global.hpp"
#include "Engine/Updater.hpp"
#include "Engine/Game.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Assets.hpp"
#include "Engine/SceneStack.hpp"
#include "Engine/Input.hpp"
#include "Engine/GUI.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace con::priv
{
GlobalClass::GlobalClass() :
	_Updater( *( new UpdaterClass{} ) ),
	Game( *( new GameClass{} ) ),
	GameWindow( *( new sf::RenderWindow{} ) ),
	_Renderer( *( new RendererClass{} ) ),
	Assets( *( new AssetsClass{} ) ),
	SceneStack( *( new SceneStackClass{} ) ),
	Input( *( new InputClass{} ) ),
	GUI( *( new GUIClass{} ) ),
	GlobalLogger( *( new GlobalLoggerClass{} ) )
{}

// Delete some pts to call their destructors.
GlobalClass::~GlobalClass()
{
	delete &Assets;
}
}

namespace con
{
inline priv::GlobalClass Global{};
}