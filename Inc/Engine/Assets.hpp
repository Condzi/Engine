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

	TextureHolder Texture;
	FontHolder Font;
	// @Note: Doens't have default font. (issue with raw literals)
	BitmapFontHolder BitmapFonts; // @ToDo change names of all things here to plural. This one is plural to avoid amibiouty with BitmapFont class.
	SoundHolder Sound;
	MusicHolder Music;
	SettingsClass Settings;

private:
	void setDefaultTexture();
	// Probably won't be used because TGUI already has it default font.
	void setDefaultFont();
};
}