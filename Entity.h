#pragma once

#include "utils/AssetsManager.h"

class Entity
{
public:
	Entity(const char* filePath, SDL_Renderer* renderer)
		: _filePath(filePath), _renderer(renderer), _texture(AssetsManager::loadTexture(filePath, renderer))
	{}

	void update() {
		_x = _x + double(velX) * _SPEED;
		_y = _y + double(velY) * _SPEED;
	}

	void draw() {
		SDL_Rect srcRect, destRect;

		srcRect.w = destRect.w = _width;
		srcRect.h = destRect.h = _height;
		srcRect.x = srcRect.y = 0;
		destRect.x = _x;
		destRect.y = _y;

		SDL_RenderCopy(_renderer, _texture, &srcRect, &destRect);
	}

	// TODO: create Vector2F class to handle x and y
	void setX(double x) {
		_x = x;
	}

	void setY(double y) {
		_y = y;
	}

	double getX() {
		return _x;
	}

	double getY() {
		return _y;
	}

	int getWidth() {
		return _width;
	}

	int getHeight() {
		return _height;
	}

	int velX, velY;
private:
	int _SPEED = 3.15;
	int _width = 16;
	int _height = 23;
	double _x = 100;
	double _y = 100;
	const char* _filePath;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
};