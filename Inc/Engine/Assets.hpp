/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/BasicAssetHolder.hpp"
#include "Engine/AudioHolder.hpp"
#include "Engine/Settings.hpp"

namespace con::priv
{
class AssetsClass final
{
public:
	AssetsClass();

	TextureHolder Textures;
	FontHolder Fonts;
	BitmapFontHolder BitmapFonts;
	SoundHolder Sound;
	MusicHolder Music;
	SettingsClass Settings;

private:
	void setFallbackTexture();
	// Probably won't be used because TGUI already has it default font.
	void setFallbackFont();
	void setFallbackBitmapFont();
};
}