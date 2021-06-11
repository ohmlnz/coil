#pragma once
#include "SDL.h"
#include "./utils/GraphicsManager.h"

class PlayerGraphics : public GraphicsManager
{
public:
	PlayerGraphics(const char* filePath, SDL_Renderer* renderer)
		: GraphicsManager(filePath, renderer)
	{}

	virtual void update(Entity& entity) {
		entity.setX(entity.getX() + double(entity.getVelX()) * _SPEED);
		entity.setY(entity.getY() + double(entity.getVelY()) * _SPEED);
	}

	virtual void render(Entity& entity) {
		SDL_Rect srcRect, destRect;

		srcRect.w = destRect.w = entity.getWidth();
		srcRect.h = destRect.h = entity.getHeight();
		srcRect.x = entity.getDirection();
		// y value will be defined by the animate method below
		srcRect.y = 0;
		destRect.x = entity.getX();
		destRect.y = entity.getY();

		SDL_RenderCopy(_renderer, _texture, &srcRect, &destRect);
	}

	virtual void animate(Entity& entity) {
		//for (auto& val : _animations["frames"].items()) {
		//	std::cout << val.key() << std::endl;
		//}
	}

private:
	// TODO: should it be part of PhysicsManager?
	int _SPEED = 3.15;
};