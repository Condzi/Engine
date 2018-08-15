/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <intrin.h>

#include "Engine/EnginePCH.hpp"
#include "Engine/Utility.hpp"


namespace con
{
#if _DEBUG
constexpr bool IS_DEBUG = true;
#else
constexpr bool IS_DEBUG = false;
#endif

#define DebugBreak() __debugbreak()

enum class LogPriority
{
	Info, Warning, Error
};

namespace priv
{
class LogFile final
{
private:
	static constexpr const char* LOG_FILE_PATH = "log.txt";
	std::vector<std::string> content;

	~LogFile();

public:
	static void append( const std::string& message );
};

class ILoggerBase
{
public:
	virtual std::string loggerName() const = 0;

	template <typename ...TArgs>
	void log( LogPriority priority, TArgs&& ...args )
	{
		auto message = ConvertTo<std::string>( "[", logPriorityToString( priority ), "] ", loggerName(), ": ", std::forward<TArgs>( args )... );
		LogFile::append( message );
		std::puts( message.c_str() );
	}

	template <typename ...TArgs>
	void debugLog( LogPriority priority, TArgs&& ...args )
	{
		if constexpr (IS_DEBUG)
			log( priority, std::forward<TArgs>( args )... );
	}

	template <typename ...TArgs>
	void print( LogPriority priority, const char* src, TArgs&& ...args )
	{
		std::string message;
		if constexpr ( sizeof...( TArgs ) > 0 )
		{
			message.reserve( std::strlen( src ) * 4 );
			printImpl( message, src, std::forward<TArgs>( args )... );
		} else
			message = src;

		message = ConvertTo<std::string>( "[", logPriorityToString( priority ), "] ", loggerName(), ": ", message );
		LogFile::append( message );
		std::puts( message.c_str() );
	}

private:
	template <typename T, typename ...TArgs>
	void printImpl( std::string& buffer, const char* src, T&& arg, TArgs&&... args )
	{
		while ( *src ) {
			if ( *src == '%' ) {
				buffer += ConvertTo<std::string>( std::forward<T>( arg ) );
				++src;

				if constexpr ( sizeof...( TArgs ) > 0 )
					printImpl( buffer, src, std::forward<TArgs>( args )... );

				break;
			} else {
				buffer += *src;

				++src;
			}

		}
	}
	const char* logPriorityToString( LogPriority priority ) const noexcept;
};
}

class ILogger :
	protected priv::ILoggerBase
{};
}

namespace con::priv
{
class GlobalLoggerClass final :
	public ILoggerBase
{
public:
	std::string loggerName() const override
	{
		return "Global";
	}
};
}