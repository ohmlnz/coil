#pragma once
#include "SDL.h"
#include <iostream>
#include "../World.h"

class Debugger
{
public:
	Debugger(World* world)
		: _world(world)
	{}

	void update(SDL_Event* event)
	{
		switch (event->type)
		{
			case SDL_KEYUP:
				switch (event->key.keysym.scancode)
				{
					case SDL_SCANCODE_R:
						if (wasMapReloaded == false)
						{
							_world->reloadMap();
							wasMapReloaded = true;
						}
						break;
				}
				break;
		}
	}
private:
	World* _world;
	bool wasMapReloaded = false;
};