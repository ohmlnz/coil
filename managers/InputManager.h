#pragma once

class Entity;

class InputManager
{
public:
	virtual ~InputManager() {}

	virtual void update(Entity& entity, SDL_Event* event) = 0;
};