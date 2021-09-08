#pragma once
#include "SDL.h"
#include "../libs/json.h"
#include <fstream>
#include <iostream>

struct entityData
{
	int width;
	int height;
	double x;
	double y;
	const char* texture;
};

class Entity;
class TileMap;

class GraphicsManager
{
public:
	virtual ~GraphicsManager() {}
	GraphicsManager(entityData data, SDL_Renderer* renderer)
		:	_renderer(renderer)
	{
		std::ifstream inputFile(data.texture);
		inputFile >> _animations;
		std::string imagePath = "assets/sprites/" + std::string(_animations["meta"]["image"]);
		_width = data.width;
		_height = data.height;
		_x = data.x;
		_y = data.y;
		_texture = AssetsManager::loadTexture(imagePath.c_str(), renderer);
	}
	virtual void initialize(Entity& entity) = 0;
	virtual void update(Entity& entity, TileMap* map) = 0;
	virtual void render(Entity& entity, bool& shouldBeAnimated) = 0;
	virtual void animate(Entity& entity) = 0;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	nlohmann::json _animations;
	int _width;
	int _height;
	double _x;
	double _y;
};
