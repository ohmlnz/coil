#pragma once
#include "SDL.h"
#include "../libs/json.h"
#include <fstream>

class Entity;

class GraphicsManager
{
public:
	virtual ~GraphicsManager() {}
	GraphicsManager(const char* filePath, SDL_Renderer* renderer)
		:	_renderer(renderer)
	{
		std::ifstream inputFile(filePath);
		inputFile >> _animations;
		std::string imagePath = "assets/sprites/" + std::string(_animations["meta"]["image"]);
		_texture = AssetsManager::loadTexture(imagePath.c_str(), renderer);
	}
	virtual void update(Entity& entity, TileMap* map) = 0;
	virtual void render(Entity& entity, bool& shouldBeAnimated) = 0;
	virtual void animate(Entity& entity) = 0;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	nlohmann::json _animations;
};
