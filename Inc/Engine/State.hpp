/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/Debug.hpp"

namespace con
{
class StateMachine;

// Obscured clone of Scene.
class State :
	public ILogger
{
public:
	using StateID = std::string_view;

	enum class Status : int8_t
	{
		Enabled, Disabled
	};

	const StateID Id = "unregistred";
	StateMachine* StateMachine;

	RULE_OF_FIVE( State );

	void _setId( StateID Id_ );

	virtual void onPush() {}
	virtual void onPop() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUpdate() {}

	void enable();
	void disable();
	void _update();

	Status getStatus() const;

private:
	Status status;

	std::string loggerName() const override;
};
}