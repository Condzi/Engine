/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/IUpdatable.hpp"
#include "Engine/Scene.hpp"

namespace con::priv
{
class SceneFactory final :
	public ILogger
{
public:
	using FactoryFunction = std::function<std::unique_ptr<Scene>()>;
	using SceneID = std::string_view;

	std::unordered_map<SceneID, FactoryFunction> functions;

	std::unique_ptr<Scene> createScene( SceneID id );

private:
	std::string loggerName() const override
	{
		return "Scene Factory";
	}
};

class SceneStackClass final :
	public IUpdatable,
	public ILogger
{
public:
	using SceneID = SceneFactory::SceneID;

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
		SceneID scene;
	};

public:
	template <typename TScene>
	void registerScene( SceneID id )
	{
		static_assert( std::is_base_of_v<Scene, TScene> );
		factory.functions[id] = [&] {
			return std::make_unique<TScene>();
		};
	}

	void push( SceneID id );
	void pop();
	void enableCurrentScene();
	void disableCurrentScene();

	std::optional<Scene*> getSceneOnTop();

	int8_t getUpdatePriority() const override
	{
		return UpdatePriority::Renderer;
	}

private:
	SceneFactory factory;
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<Action> pendingActions;
	std::vector<Action> actionBuffer;

	std::string loggerName() const override
	{
		return "Scene Stack";
	}

	void requestAction( Action&& action );

	void applyPush( SceneID id );
	void applyPop();
	void applyEnable();
	void applyDisable();

	void applyActions();
	void updateScenes();
	void update() override;
};
}