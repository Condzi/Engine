/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/SystemStorage.hpp"

namespace con::priv
{
SystemStorage::SystemStorage( Scene* parentScene_ ) :
	parentScene( *parentScene_ )
{}
void SystemStorage::updateSystems()
{
	if ( needsSort )
		update();

	for ( auto& system : systems )
		system->onUpdate();
}

void SystemStorage::update()
{
	if ( needsSort ) {
		needsSort = false;

		std::sort( systems.begin(), systems.end(), []( auto& a, auto& b ) {
			return a->_getUpdatePriority() < b->_getUpdatePriority();
		} );
	}
}
}
