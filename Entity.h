#pragma once

#include "AssetsManager.h"

class Entity
{
public:
	Entity() {};

	Entity(const char* filePath, SDL_Renderer* renderer) : _filePath(filePath), _renderer(renderer) {
		_texture = AssetsManager::LoadTexture(filePath, renderer);
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

private:
	int _height = 45;
	int _width = 32;
	double _x = 50;
	double _y = 50;
	const char* _filePath;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
};