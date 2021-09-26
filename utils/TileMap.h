#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "../libs/cute_tiled.h"
#include "../managers/AssetsManager.h"
#include "../managers/AnimationManager.h"
#include <vector>
#include "TreeLoader.h"

// TODO: investigate forward reference
class Entity;
class World;

class TileMap
{
public:
	TileMap() {}
	TileMap(SDL_Renderer* renderer, Node* node);
	~TileMap();
	void render();
	void update(Entity* player, World* world);
	void loadNextMap();
	int getMapWidth() const;
	int getMapHeight() const;
	int getBlockSize() const;
	int convertToDoorIndex(int doorIndex);
	void animate();
	struct cute_tiled_tile_descriptor_t& getTile(int id);
	bool isTileAnimated(int id) const;
	bool isTileCollidable(int indexes[]);
	bool isAnimationCurrentlyRunning(int id, int position) const;
	bool isLoadingMap = false;
private:
	int const _tilesetWidth = 10;
	int const _BLOCK_SIZE = 16;
	int _mapTotalBlocks;
	int _mapWidth;
	int _mapHeight;
	Entity* _player;
	World* _world;
	SDL_Renderer* _renderer;
	SDL_Texture* _mapTexture;
	cute_tiled_map_t* _mapData;
	Node* _currentNode;
	std::vector<AnimationManager*> animatedTiles;
	std::string _texturePath = "assets/maps/dungeon-atlas.png";
};