/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Engine/EnginePCH.hpp"

#include "Engine/Debug.hpp"

#ifdef _WIN32
#undef DebugBreak()

#include <windows.h>
#endif

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

void ILoggerBase::setConsoleTextColor( LogPriority priority )
{
#ifdef _WIN32
	uint8_t color = 7;
	switch ( priority ) {
		case LogPriority::Info: color = 15; break; // lighter grey
		case LogPriority::Warning: color = 14; break; // light yellow
		case LogPriority::Error: color = 12; break; // light red
	}

	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
#endif
}

void ILoggerBase::resetConsoleTextColor()
{
#ifdef _WIN32
	// light grey
	uint8_t color = 7;
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
#endif
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
