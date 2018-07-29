/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Debug.hpp"

namespace con::priv
{
const char* ILoggerBase::logPriorityToString( LogPriority priority ) const noexcept
{
	switch ( priority ) {
	case LogPriority::Info:	return "INFO";
	case LogPriority::Warning: return "WARN";
	case LogPriority::Error: return " ERR";
	}

	return "";
}

LogFile::~LogFile()
{
	std::experimental::filesystem::remove( { LOG_FILE_PATH } );
	
	std::ofstream logFile( LOG_FILE_PATH );
	std::move( content.begin(), content.end(), std::ostream_iterator<std::string>( logFile, "\n" ) );
	content.clear();
}

void LogFile::append( const std::string& message )
{
	static LogFile file;
	file.content.emplace_back( message );
}
}
