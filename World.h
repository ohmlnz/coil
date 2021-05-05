#pragma once
#include "utils/TileMap.h"
#include "utils/TreeLoader.h"
#include "Entity.h"
#include <vector>

class World
{
public:
	World(SDL_Renderer* renderer);
	~World();
	void loadMap(Node* node);
	void unloadMap(TileMap* map);
	void events(SDL_Event* _event);
	void render(double lag);
	void update();
private:
	std::vector<Entity*> _entities;
	TileMap* _map;
	Entity* _testPlayer;
	SDL_Renderer* _renderer;
	Node* _currentNode;
	const std::string _rootPath;
};