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
		if constexpr ( IS_DEBUG )
			log( priority, std::forward<TArgs>( args )... );
	}

	template <typename ...TArgs>
	void print( LogPriority priority, const char* src, TArgs&& ...args )
	{

		resetConsoleTextColor();
		std::cout << "[";
		setConsoleTextColor( priority );
		std::cout << logPriorityToString( priority );
		resetConsoleTextColor();
		std::cout << "] " << loggerName() << ": ";

		std::string message;
		if constexpr ( sizeof...( TArgs ) > 0 )
		{
			message.reserve( std::strlen( src ) * 4 );
			printImpl( message, src, priority, std::forward<TArgs>( args )... );
		} else {
			std::cout << src;
			message = src;
		}
		std::cout << '\n';

		message = ConvertTo<std::string>( "[", logPriorityToString( priority ), "] ", loggerName(), ": ", message );
		LogFile::append( message );
	}

private:
	template <typename T, typename ...TArgs>
	void printImpl( std::string& buffer, const char*& src, LogPriority priority, T&& arg, TArgs&&... args )
	{
		while ( *src ) {
			if ( *src == '%' ) {
				auto argStr = ConvertTo<std::string>( std::forward<T>( arg ) );
				buffer += argStr;
				setConsoleTextColor( priority );
				std::cout << argStr;
				resetConsoleTextColor();
				++src;

				if constexpr ( sizeof...( TArgs ) > 0 )
					printImpl( buffer, src, priority, std::forward<TArgs>( args )... );

			} else {
				buffer += *src;
				std::cout << *src;

				++src;
			}

		}
	}
	const char* logPriorityToString( LogPriority priority ) const noexcept;
	void setConsoleTextColor( LogPriority priority );
	void resetConsoleTextColor();
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