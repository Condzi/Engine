/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/EnginePCH.hpp"
#include "Engine/Debug.hpp"
#include "Engine/BitmapFont.hpp"

namespace con::priv
{
template <typename TAsset>
class BasicAssetHolder :
	public ILogger
{
public:
	using Hasher = std::hash<std::string>;

	virtual ~BasicAssetHolder() = default;

	bool load( const std::string& path, size_t hash )
	{
		if ( TAsset asset; asset.loadFromFile( path ) ) {
			assets[hash] = std::move( asset );
			return true;
		} else {
			print( LogPriority::Error, "can't load %.", path );
			return false;
		}
	}

	bool load( const std::string& path, const std::string& name )
	{
		return load( path, Hasher{}( name ) );
	}

	const TAsset& get( size_t hash )
	{
		if ( auto it = assets.find( hash ); it != assets.end() )
			return it->second;
		else {
			print( LogPriority::Warning, "can't find (hash: %).", hash );
			return fallback;
		}
	}

	const TAsset& get( const std::string& name )
	{
		if ( auto it = assets.find( Hasher{}( name ) ); it != assets.end() )
			return it->second;
		else {
			print( LogPriority::Warning, "can't find %.", name );
			return fallback;
		}
	}

	void _setFallback( TAsset&& asset )
	{
		fallback = std::move( asset );
	}

	const TAsset& getFallback() const
	{
		return fallback;
	}

private:
	TAsset fallback;
	std::unordered_map<size_t, TAsset> assets;
};

class TextureHolder final :
	public BasicAssetHolder<sf::Texture>
{
private:
	std::string loggerName() const override
	{
		return "Texture Holder";
	}
};

class FontHolder final :
	public BasicAssetHolder<sf::Font>
{
private:
	std::string loggerName() const override
	{
		return "Font Holder";
	}
};

class BitmapFontHolder final :
	public BasicAssetHolder<BitmapFont>
{
private:
	std::string loggerName() const override
	{
		return "Bitmap Font Holder";
	}
};
}