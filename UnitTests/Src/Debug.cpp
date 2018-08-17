/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Catch.hpp"

#include "Engine/Debug.hpp"

TEST_CASE( "Global Logger", "[DEBUG]" )
{
	con::Global.Logger.log( con::LogPriority::Info, "Global logger!" );
}

TEST_CASE( "print", "[DEBUG]" )
{
	con::Global.Logger.print( con::LogPriority::Info, "Test" );
	con::Global.Logger.print( con::LogPriority::Info, "Test2 = %.", "Test2" );
	con::Global.Logger.print(con::LogPriority::Warning, "I'm a %!", "warning");
	con::Global.Logger.print( con::LogPriority::Error, "I'm an %!", "error" );
}