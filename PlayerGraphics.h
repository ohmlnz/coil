#pragma once
#include "SDL.h"
#include "./utils/GraphicsManager.h"

class PlayerGraphics : public GraphicsManager
{
public:
	PlayerGraphics(const char* filePath, SDL_Renderer* renderer)
		: GraphicsManager(filePath, renderer)
	{}

	// TODO: should not be part of the graphics component
	virtual void update(Entity& entity, TileMap* map) {
		entity.setX(map, entity.getX() + double(entity.getVelX()) * _SPEED);
		entity.setY(map, entity.getY() + double(entity.getVelY()) * _SPEED);
	}

	virtual void render(Entity& entity, bool& shouldBeAnimated) {
		if (shouldBeAnimated)
		{
			animate(entity);
		}

		SDL_Rect srcRect, destRect;

		srcRect.w = destRect.w = entity.getWidth();
		srcRect.h = destRect.h = entity.getHeight();
		srcRect.x = srcRectX;
		srcRect.y = srcRectY;
		destRect.x = entity.getX();
		destRect.y = entity.getY();

		SDL_RenderCopy(_renderer, _texture, &srcRect, &destRect);
	}

	virtual void animate(Entity& entity) {
	
		// We're mapping enum values to strings so we can find them in the json object
		// TODO: explore other solutions

		std::string playerState[4] = { "idle", "walking", "running", "shooting" };
		std::string playerDirections[4] = { "down", "right", "left", "up" };

		std::string currentState = playerState[entity.getState()];
		std::string currentDirection = playerDirections[entity.getDirection()];
		int animationLength = _animations[currentState][currentDirection]["length"];

		// TODO: take into consideration 'duration' key to slow down/speed up animations
		if (currentIndex >= animationLength) {
			currentIndex = 0;
		}

		std::string objectKey = currentDirection + "-" + std::to_string(currentIndex);
		srcRectX = _animations[currentState][currentDirection][objectKey]["frame"]["x"];
		srcRectY = _animations[currentState][currentDirection][objectKey]["frame"]["y"];
		currentIndex++;
	}

private:
	// TODO: should it be part of PhysicsManager?
	int _SPEED = 3.15;
	int srcRectY;
	int srcRectX;
	int currentIndex = 0;
};