/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "Engine/IUpdatable.hpp"
#include "Engine/Drawable.hpp"

namespace con::priv
{
class RendererClass final :
	public IUpdatable
{
public:
	int8_t getUpdatePriority() const override
	{
		return UpdatePriority::Renderer;
	}

	void add( IDrawable* drawable );
	void remove( IDrawable* drawable );

private:
	std::vector<IDrawable*> drawables;

	void sortByLayer();
	void render();
	void update() override;
};
}