/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/SceneStack.hpp"

namespace con::priv
{
std::unique_ptr<Scene> SceneFactory::createScene( SceneID id )
{
	auto result = functions.find( id );
	if ( result != functions.end() )
		return result->second();

	print( LogPriority::Error, "no scene of id %.", id );
	return nullptr;
}

void SceneStackClass::push( SceneID id )
{
	requestAction( { Operation::Push, id } );
}

void SceneStackClass::pop()
{
	requestAction( { Operation::Pop } );
}

void SceneStackClass::enableCurrentScene()
{
	requestAction( { Operation::Enable } );
}

void SceneStackClass::disableCurrentScene()
{
	requestAction( { Operation::Disable } );
}

std::optional<Scene*> SceneStackClass::getSceneOnTop()
{
	if ( scenes.empty() )
		return {};

	return scenes.back().get();
}

void SceneStackClass::requestAction( Action&& action )
{
	auto op = [&] {
		switch ( action.operation ) {
		case Operation::Push: return "Push";
		case Operation::Pop: return "Pop";
		case Operation::Enable: return "Enable";
		case Operation::Disable: return "Disable";
		}
	}( );

	if ( action.operation == Operation::Push )
		print( LogPriority::Info, "request %, scene id: %.", op, action.scene );
	else
		print( LogPriority::Info, "request %.", op );

	actionBuffer.emplace_back( std::move( action ) );
}

void SceneStackClass::applyPush( SceneID id )
{
	auto scene = factory.createScene( id );
	if ( scene ) {
		scene->_setId( id );
		// passing 'Push' as argument to have coloring.
		print( LogPriority::Info, "applying %, scene id: %.", "Push", id );
		scenes.emplace_back( std::move( scene ) )->onPush();
	} else
		print( LogPriority::Error, "failed to apply %, scene id: %.", "Push", id );
}

void SceneStackClass::applyPop()
{
	if ( scenes.empty() )
		return print( LogPriority::Error, "failed to apply %: empty stack.", "Pop" );

	print( LogPriority::Info, "applying %, scene id: %.", "Pop", scenes.back()->Id );
	scenes.back()->onPop();
	scenes.pop_back();
}

void SceneStackClass::applyEnable()
{
	if ( scenes.empty() )
		return print( LogPriority::Error, "failed to apply %: empty stack.", "Enable" );

	scenes.back()->enable();
}

void SceneStackClass::applyDisable()
{
	if ( scenes.empty() )
		return print( LogPriority::Error, "failed to apply %: empty stack.", "Disable" );

	scenes.back()->disable();
}

void SceneStackClass::applyActions()
{
	pendingActions = actionBuffer;
	actionBuffer.clear();
	// Action is that small it's not worth using reference
	for ( auto action : pendingActions ) {
		switch ( action.operation ) {
		case Operation::Push: applyPush( action.scene ); break;
		case Operation::Pop: applyPop(); break;
		case Operation::Enable: applyEnable(); break;
		case Operation::Disable: applyDisable(); break;
		}
	}

	pendingActions.clear();
}

void SceneStackClass::updateScenes()
{
	for ( auto& scene : scenes )
		scene->_update();
}

void SceneStackClass::update()
{
	applyActions();
	updateScenes();
}
}