/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Scene.hpp"

namespace con
{
void Scene::_setId( SceneID Id_ )
{
	const_cast<std::string_view&>( Id ) = Id_;
}

void Scene::enable()
{
	if ( status == Status::Enabled )
		debugLog( LogPriority::Warning, "already enabled." );
	else {
		status = Status::Enabled;
		enableEntities();
		onEnable();
	}
}

void Scene::disable()
{
	if ( status == Status::Enabled ) {
		status = Status::Disabled;
		onDisable();
		disableEntities();
	}
	else 
		debugLog( LogPriority::Warning, "already disabled." );
}

void Scene::_update()
{
	if ( status != Status::Enabled )
		return;

	systems.updateSystems();
	onUpdate();
}

std::string Scene::loggerName() const
{
	static auto getStatusAsString = []( Status s ) {
		switch ( s ) {
		case Status::Enabled: return "Enabled";
		case Status::Disabled: return "Disabled";
		}
	};

	return ConvertTo<std::string>( Id, ":", getStatusAsString( status ) );
}

void Scene::disableEntities()
{
	forEachEntity( []( Entity& entity ) {
		entity.disable();
	} );
}

void Scene::enableEntities()
{
	forEachEntity( []( Entity& entity ) {
		entity.enable();
	} );
}
}