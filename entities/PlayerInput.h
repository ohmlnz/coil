#pragma once
#include "../managers/InputManager.h"

enum controllerButtons
{
	B,
	A,
	Y,
	X,
	L,
	R,
	SELECT,
	START,
};

class PlayerInput : public InputManager
{
public:
	virtual void update(Entity& entity, SDL_Event* event) {
		switch (event->type)
		{
			case SDL_KEYDOWN:
				entity.getStateManager()->setState(WALKING);
				switch (event->key.keysym.scancode)
				{
					case SDL_SCANCODE_UP:
						entity.getStateManager()->setDirection(UP);
						entity.setVelocity(entity.getVelocity()._velX, -1);
						break;
					case SDL_SCANCODE_LEFT:
						entity.getStateManager()->setDirection(LEFT);
						entity.setVelocity(-1, entity.getVelocity()._velY);
						break;
					case SDL_SCANCODE_DOWN:
						entity.getStateManager()->setDirection(DOWN);
						entity.setVelocity(entity.getVelocity()._velX, 1);
						break;
					case SDL_SCANCODE_RIGHT:
						entity.getStateManager()->setDirection(RIGHT);
						entity.setVelocity(1, entity.getVelocity()._velY);
						break;
				}
				break;
			//case SDL_JOYAXISMOTION:
			//	if (event->jaxis.which == 0)
			//	{
			//		if (event->jaxis.axis == 0)
			//		{
			//			if (event->jaxis.value < -JOYSTICK_DEAD_ZONE)
			//			{
			//				entity.setVelocity(-1, entity.getVelocity()._velY);
			//			}
			//			else if (event->jaxis.value > JOYSTICK_DEAD_ZONE)
			//			{
			//				entity.setVelocity(1, entity.getVelocity()._velY);
			//			}
			//			else
			//			{
			//				entity.setVelocity(0, entity.getVelocity()._velY);
			//			}
			//		}
			//		else if (event->jaxis.axis == 1)
			//		{
			//			if (event->jaxis.value < -JOYSTICK_DEAD_ZONE)
			//			{
			//				entity.setVelocity(entity.getVelocity()._velX, -1);
			//			}
			//			else if (event->jaxis.value > JOYSTICK_DEAD_ZONE)
			//			{
			//				entity.setVelocity(entity.getVelocity()._velX, 1);
			//			}
			//			else
			//			{
			//				entity.setVelocity(entity.getVelocity()._velX, 0);
			//			}
			//		}
			//	}
			//	break;
			//case SDL_JOYBUTTONDOWN:
			//	switch (int(event->jbutton.button))
			//	{
			//		//case B:
			//		//case A:
			//		//case Y:
			//		//case X:
			//		//case L:
			//		//case R:
			//		//case SELECT:
			//		//case START:
			//	}
			//	break;
			case SDL_JOYHATMOTION:
				entity.getStateManager()->setState(WALKING);
				switch (event->jhat.value)
				{
					case SDL_HAT_UP:
						entity.getStateManager()->setDirection(UP);
						entity.setVelocity(entity.getVelocity()._velX, -1);
						break;
					case SDL_HAT_LEFT:
						entity.getStateManager()->setDirection(LEFT);
						entity.setVelocity(-1, entity.getVelocity()._velY);
						break;
					case SDL_HAT_DOWN:
						entity.getStateManager()->setDirection(DOWN);
						entity.setVelocity(entity.getVelocity()._velX, 1);
						break;
					case SDL_HAT_RIGHT:
						entity.getStateManager()->setDirection(RIGHT);
						entity.setVelocity(1, entity.getVelocity()._velY);
						break;
					case SDL_HAT_CENTERED:
						entity.getStateManager()->setState(IDLE);
						entity.setVelocity(0, 0);
						break;
				}
				break;
			default:
				entity.getStateManager()->setState(IDLE);
				entity.setVelocity(0, 0);
				break;
		}
	}

private:
	// SDL converts the stick position into a number between -32768 and 32767. 
	// This deadzone allows us to define a window we can ignore, thus avoiding
	// light taps on the stick.
	const int JOYSTICK_DEAD_ZONE = 8000;
};