/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/IUpdatable.hpp"
#include "Engine/Debug.hpp"

namespace con
{
class Scene;

class Entity :
	public IUpdatable,
	public ILogger,
	public sf::NonCopyable
{
public:
	RULE_OF_FIVE( Entity );
	virtual ~Entity() = default;

	enum class Status : int8_t
	{
		Enabled,
		Disabled,
		Dead
	};

	// @ToDo: Wrong naming convention. Change to 'Position'! 
	Vec2f position;
	// @ToDo: Wrong naming convention. Change to 'Tag'!
	std::string tag = "UnnamedEntity";

	void kill();
	void disable();
	void enable();

	int8_t getUpdatePriority() const final
	{
		return UpdatePriority::Entity;
	}

	Status getStatus() const;
	Scene& getParentScene();
	int32_t getUniqueID();

	virtual void onSpawn() {}
	virtual void onKill() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUpdate() {}

	void _setParentScene( Scene& scene );

private:
	Status status = Status::Enabled;
	Scene* parentScene = nullptr;
	inline static int32_t UNIQUE_ID_COUNTER = 0;
	const int32_t uniqueID = UNIQUE_ID_COUNTER++;

	void update() override final;
	std::string loggerName() const override final;
};
}