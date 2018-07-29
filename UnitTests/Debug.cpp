/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include "Engine/Debug.hpp"

TEST_CASE( "Global Logger", "[DEBUG]" )
{
	con::Global.GlobalLogger.log( con::LogPriority::Info, "Global logger!" );
}