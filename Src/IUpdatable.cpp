/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/IUpdatable.hpp"
#include "Engine/Updater.hpp"

namespace con
{
IUpdatable::IUpdatable()
{
	Global._Updater.add( this );
}

IUpdatable::~IUpdatable()
{
	Global._Updater.remove( this );
}
}
