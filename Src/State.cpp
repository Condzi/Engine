/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/State.hpp"

namespace con
{
void State::_setId( StateID Id_ )
{
	const_cast<StateID&>( Id ) = Id_;
}

void State::enable()
{
	if ( status == Status::Enabled )
		debugLog( LogPriority::Warning, "already enabled." );
	else {
		status = Status::Enabled;
		onEnable();
	}
}

void State::disable()
{
	if ( status == Status::Enabled ) {
		status = Status::Disabled;
		onDisable();
	}
	else 
		debugLog( LogPriority::Warning, "already disabled." );
}

void State::_update()
{
	if ( status == Status::Enabled )
		onUpdate();
}

State::Status State::getStatus() const
{
	return status;
}

std::string State::loggerName() const
{
	return Id.data();
}
}