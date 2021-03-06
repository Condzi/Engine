/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/Utility.hpp"

namespace con
{
class IUpdatable
{
public:
	IUpdatable();
	RULE_OF_FIVE_NO_CTOR( IUpdatable );
	
	virtual ~IUpdatable();

	virtual int8_t getUpdatePriority() const = 0;
	virtual void update() = 0;
};
}