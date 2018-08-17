/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/EntityStorage.hpp"

#include <SFML/System/Clock.hpp>

namespace con::priv
{
void EntityStorage::update()
{
	if ( cleanupClock.getElapsedTime() >= CLEANUP_INTERVAL ) {
		cleanupClock.restart();

		cleanup();
	}
}

std::unique_ptr<Entity>& EntityStorage::getFreeSlot()
{
	for ( auto& e : entities )
		if ( !e )
			return e;

	print( LogPriority::Warning, "No free slots: has to realloc. (% items)", entities.size() );
	return entities.emplace_back();
}

void EntityStorage::cleanup()
{
	for ( auto& e : entities )
		if ( e && e->getStatus() == Entity::Status::Dead )
			e.reset();
}
}