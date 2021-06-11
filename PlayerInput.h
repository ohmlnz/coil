#pragma once
#include "./utils/InputManager.h"

class PlayerInput : public InputManager
{
public:
	virtual void update(Entity& entity, SDL_Event* event) {
		switch (event->type)
		{
			case SDL_KEYDOWN:
				entity.setState(WALKING);
				switch (event->key.keysym.scancode)
				{
					case SDL_SCANCODE_UP:
						entity.setDirection(UP);
						entity.setVelY(-1);
						break;
					case SDL_SCANCODE_LEFT:
						entity.setDirection(LEFT);
						entity.setVelX(-1);
						break;
					case SDL_SCANCODE_DOWN:
						entity.setDirection(DOWN);
						entity.setVelY(1);
						break;
					case SDL_SCANCODE_RIGHT:
						entity.setDirection(RIGHT);
						entity.setVelX(1);
						break;
				}
				break;
			case SDL_KEYUP:
				entity.setState(IDLE);
				entity.setVelX(0);
				entity.setVelY(0);
				break;
			case SDL_JOYAXISMOTION:
				if (event->jaxis.which == 0)
				{
					if (event->jaxis.axis == 0)
					{
						if (event->jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							entity.setVelX(-1);
						}
						else if (event->jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							entity.setVelX(1);
						}
						else
						{
							entity.setVelX(0);
						}
					}
					else if (event->jaxis.axis == 1)
					{
						if (event->jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							entity.setVelY(-1);
						}
						else if (event->jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							entity.setVelY(1);
						}
						else
						{
							entity.setVelY(0);
						}
					}
				}
				break;
		}
	}
private:
	// SDL converts the stick position into a number between -32768 and 32767. 
	// This deadzone allows us to define a window we can ignore, thus avoiding
	// light taps on the stick.
	const int JOYSTICK_DEAD_ZONE = 8000;
};