/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/State.hpp"

namespace con::priv
{
class StateFactory final :
	public ILogger
{
public:
	using FactoryFunction = std::function<std::unique_ptr<State>()>;
	using StateID = State::StateID;

	std::unordered_map<StateID, FactoryFunction> functions;

	std::unique_ptr<State> createState( StateID id );

private:
	std::string loggerName() const override
	{
		return "State Factory";
	} 
};
}

namespace con
{
class StateMachine final :
	public ILogger
{
	public:
	using StateID = priv::StateFactory::StateID;

private:
	enum class Operation : int8_t
	{
		Push,
		Pop,
		Enable,
		Disable
	};

	struct Action final
	{
		Operation operation = Operation::Push;
		StateID state;
	};

public:
	template <typename TScene>
	void registerState( StateID id )
	{
		static_assert( std::is_base_of_v<State, TScene> );
		factory.functions[id] = [&] {
			return std::make_unique<TScene>();
		};
	}

	void push( StateID id );
	void pop();
	void enableCurrentState();
	void disableCurrentState();
	void update();

	std::optional<State*> getStateOnTop();

private:
	priv::StateFactory factory;
	std::vector<std::unique_ptr<State>> states;
	std::vector<Action> pendingActions;
	std::vector<Action> actionBuffer;

	std::string loggerName() const override;

	void requestAction( Action&& action );

	void applyPush( StateID id );
	void applyPop();
	void applyEnable();
	void applyDisable();

	void applyActions();
	void updateStates();
};
}