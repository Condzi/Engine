/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/EntityStorage.hpp"
#include "Engine/SystemStorage.hpp"

namespace con
{
class Scene :
	public ILogger
{
public:
	// Same as priv::SceneFactory::SceneID
	using SceneID = std::string_view;

	enum class Status : int8_t
	{
		Enabled, Disabled
	};

	const SceneID Id = "unregistred";

	RULE_OF_FIVE( Scene );
	virtual ~Scene() = default;

	virtual void onPush() {}
	virtual void onPop() {}
	virtual void onEnable() {}
	virtual void onDisable() {}
	virtual void onUpdate() {}

	void _setId( SceneID Id_ );

	template <typename TEntity, typename ...TArgs>
	TEntity& spawn( TArgs&& ...args )
	{
		return entities.spawn<TEntity>( std::forward<TArgs>( args )... );
	}

	template <typename TEntity>
	std::vector<TEntity*> getAllEntitiesOfType()
	{
		return entities.getAllEntitiesOfType<TEntity>();
	}

	template <typename TLambda>
	void forEachEntity( TLambda&& lambda )
	{
		auto entitiesVec = getAllEntitiesOfType<Entity>();
		for ( auto* entityPtr : entitiesVec )
			lambda( *entityPtr );
	}

	// @ToDo: forEachEntityDerivedFrom<TType> ?
	// @ToDo: change TLambda to std::function<void(TType)>
	template <typename TEntity, typename TLambda>
	void forEachEntityOfType( TLambda&& lambda )
	{
		forEachEntity( [&]( Entity& entity ) {
			if ( auto* casted = dynamic_cast<TEntity*>( &entity ); casted )
				lambda( *casted );
		} );
	}

	template <typename TSystem, typename ...TArgs>
	TSystem& addSystem( int16_t updatePriority, TArgs&& ...args )
	{
		return systems.addSystem<TSystem>( updatePriority, std::forward<TArgs>( args )... );
	}

	Status getStatus() const
	{
		return status;
	}

	// Immidietly enables scene.
	void enable();
	// Immidietly disables scene.
	void disable();
	void _update();

private:
	Status status = Status::Enabled;
	priv::EntityStorage entities;
	priv::SystemStorage systems{ this };

	std::string loggerName() const final;
	void disableEntities();
	void enableEntities();
};
}