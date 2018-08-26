/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/StateMachine.hpp"

namespace con::priv
{
std::unique_ptr<State> con::priv::StateFactory::createState( StateID id )
{
	auto result = functions.find( id );
	if ( result != functions.end() ) {
		result->second()->_setId( id );
		return result->second();
	}

	print( LogPriority::Error, "no scene of id %.", id );
	return nullptr;
}
}

namespace con
{
void StateMachine::push( StateID id )
{
	requestAction( { Operation::Push, id } );
}

void StateMachine::pop()
{
	requestAction( { Operation::Pop } );
}

void StateMachine::enableCurrentState()
{
	requestAction( { Operation::Enable } );
}

void StateMachine::disableCurrentState()
{
	requestAction( { Operation::Disable } );
}

void StateMachine::update()
{
	applyActions();
	updateStates();
}

std::optional<State*> StateMachine::getStateOnTop()
{
	if ( states.empty() )
		return {};

	return states.back().get();
}

std::string StateMachine::loggerName() const
{
	return "State Machine";
}

void StateMachine::requestAction( Action && action )
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
		print( LogPriority::Info, "request %, scene id: %.", op, action.state );
	else
		print( LogPriority::Info, "request %.", op );

	actionBuffer.emplace_back( std::move( action ) );
}

void StateMachine::applyPush( StateID id )
{
	auto state = factory.createState( id );

	if ( state ) {
		state->StateMachine = this;
		// passing 'Push' as argument to have coloring.
		print( LogPriority::Info, "applying %, state id: %.", "Push", id );
		states.emplace_back( std::move( state ) )->onPush();
	} else
		print( LogPriority::Error, "failed to apply %, state id: %.", "Push", id );
}

void StateMachine::applyPop()
{
	if ( states.empty() )
		return print( LogPriority::Error, "failed to apply %: empty stack.", "Pop" );

	print( LogPriority::Info, "applying %.", "Pop" );
	states.back()->onPop();
	states.pop_back();
}

void StateMachine::applyEnable()
{
	if ( states.empty() )
		return print( LogPriority::Error, "failed to apply %: empty stack.", "Enable" );

	states.back()->enable();
}

void StateMachine::applyDisable()
{
	if ( states.empty() )
		return print( LogPriority::Error, "failed to apply %: empty stack.", "Disable" );

	states.back()->disable();
}

void StateMachine::applyActions()
{
	pendingActions = actionBuffer;
	actionBuffer.clear();
	// Action is that small it's not worth using reference
	for ( auto action : pendingActions ) {
		switch ( action.operation ) {
		case Operation::Push: applyPush( action.state ); break;
		case Operation::Pop: applyPop(); break;
		case Operation::Enable: applyEnable(); break;
		case Operation::Disable: applyDisable(); break;
		}
	}

	pendingActions.clear();
}

void StateMachine::updateStates()
{
	for ( auto& state : states )
		state->_update();
}
}
