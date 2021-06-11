#pragma once
#include "utils/TileMap.h"
#include "utils/TreeLoader.h"
#include "Entity.h"
#include <vector>
// TODO: to be removed once GraphicsManager gets added
#include "PlayerInput.h"
#include "PlayerGraphics.h"

class World
{
public:
	World(SDL_Renderer* renderer);
	~World();
	void loadMap(Node* node);
	void unloadMap(TileMap* map);
	void render(double lag);
	void update(SDL_Event* event);
private:
	std::vector<Entity*> _entities;
	TileMap* _map;
	Entity* _testPlayer;
	SDL_Renderer* _renderer;
	Node* _currentNode;
	const std::string _rootPath;
};