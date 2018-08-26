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
	Logger( *( new GlobalLoggerClass{} ) )
{}

// Order of delete matter!
GlobalClass::~GlobalClass()
{
	delete &Assets;
	delete &GUI;
	delete &Input;
	delete &SceneStack;
	delete &_Renderer;
	delete &GameWindow;
	delete &Game;
	delete &_Updater;
	delete &Logger;
}
}

namespace con
{
inline priv::GlobalClass Global{};
}