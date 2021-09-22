#pragma once
#include "libs/json.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "utils/TreeLoader.h"
#include "entities/Entity.h"
#include "entities/PlayerInput.h"
#include "entities/PlayerGraphics.h"
#include "entities/PlayerState.h"
#include "entities/EntityData.h"

class TileMap;

class World
{
public:
	World(SDL_Renderer* renderer);
	~World();
	void loadMap(Node* node);
	void unloadMap(TileMap* map);
	void loadEntities(Node* node);
	void reloadMap();
	void render(double lag);
	void update(SDL_Event* event);
private:
	std::vector<Entity*> _entities;
	Entity* _player;
	TileMap* _map;
	SDL_Renderer* _renderer;
	Node* _currentNode;
	TreeLoader* _tree;
	const std::string _rootPath;
	nlohmann::json _permutations;
};