#include "TileMap.h"
#define CUTE_TILED_IMPLEMENTATION
#include "../libs/cute_tiled.h"
#define MYNULL NULL
#include <iostream>
#include "../World.h"
#include <algorithm>

TileMap::TileMap(SDL_Renderer* renderer, Node* node)
	: _renderer(renderer), _currentNode(node)
{
	_mapTexture = AssetsManager::loadTexture(_texturePath.c_str(), _renderer);
	cute_tiled_map_t* loadedMap = cute_tiled_load_map_from_file(_currentNode->_mapPath.c_str(), NULL);
	_mapWidth = (loadedMap->width) * _BLOCK_SIZE;
	_mapHeight = (loadedMap->height) * _BLOCK_SIZE;
	_mapTotalBlocks = (_mapWidth / _BLOCK_SIZE) * (_mapHeight / _BLOCK_SIZE);
	_mapData = loadedMap;
	std::sort(_currentNode->_doorsLocation.begin(), _currentNode->_doorsLocation.end());
	return;
}

TileMap::~TileMap()
{
	cute_tiled_free_map(_mapData);
	SDL_DestroyTexture(_mapTexture);
}

void TileMap::render()
{
	cute_tiled_layer_t* layer = _mapData->layers;

	while (layer)
	{
		int* data = layer->data;
		int data_count = layer->data_count;
		for (int i = 0; i < _mapTotalBlocks; i++)
		{
			if (data[i] > 0)
			{
				if (isTileAnimated(data[i]))
				{
					if (!isAnimationCurrentlyRunning(data[i], i))
					{
						cute_tiled_tile_descriptor_t tile = getTile(data[i]);
						AnimationManager* animatedTile = new AnimationManager(data[i], i, _renderer, _mapTexture, tile);
						animatedTiles.push_back(animatedTile);
					}
				}
				else
				{
					int srcX = (data[i] - 1) % _tilesetWidth;
					int srcY = (data[i] - 1) / _tilesetWidth;

					int destX = i % (_mapWidth / _BLOCK_SIZE);
					int destY = i / (_mapWidth / _BLOCK_SIZE);

					SDL_Rect srcRect = { srcX * _BLOCK_SIZE, srcY * _BLOCK_SIZE, _BLOCK_SIZE, _BLOCK_SIZE };
					SDL_Rect destRect = { destX * _BLOCK_SIZE, destY * _BLOCK_SIZE, _BLOCK_SIZE, _BLOCK_SIZE };

					SDL_RenderCopy(_renderer, _mapTexture, &srcRect, &destRect);
				}
			}
		}
		layer = layer->next;
	}
}

void TileMap::animate()
{
	for (auto &tile : animatedTiles)
	{
		if (tile->isAnimationRunning())
		{
			tile->animateStatic(_renderer, _mapTexture);
		}
	}
}

bool TileMap::isTileCollidable(int indexes[])
{	
	if (isLoadingMap)
	{
		return false;
	}

	cute_tiled_layer_t* layer = _mapData->layers;
	int tilesIds[2];

	while (layer)
	{
		// target top layer
		if (layer->next == nullptr)
		{
			tilesIds[0] = layer->data[indexes[0]];
			tilesIds[1] = layer->data[indexes[1]];
		}
		layer = layer->next;
	}

	cute_tiled_tile_descriptor_t* tiles = _mapData->tilesets->tiles;
	const int DOOR_INDEX = 39;
	while (tiles)
	{
		if (tiles->tile_index == (tilesIds[0] - 1) || tiles->tile_index == (tilesIds[1] - 1))
		{
			if (tiles->tile_index == DOOR_INDEX)
			{
				isLoadingMap = true;
				loadNextMap();
			}
			return true;
		}

		tiles = tiles->next;
	}
	return false;
}
	
bool TileMap::isAnimationCurrentlyRunning(int id, int position) const
{
	for (auto &tile : animatedTiles)
	{
		if (tile->getId() == id && tile->getPosition() == position)
		{
			return true;
		}
	}

	return false;
}

bool TileMap::isTileAnimated(int id) const
{
	cute_tiled_tile_descriptor_t* tiles = _mapData->tilesets->tiles;

	while (tiles)
	{
		if (tiles->tile_index == (id - 1) && tiles->animation != NULL)
		{
			return true;
		}

		tiles = tiles->next;
	}
	return false;
}

struct cute_tiled_tile_descriptor_t& TileMap::getTile(int id)
{
	cute_tiled_tile_descriptor_t* tiles = _mapData->tilesets->tiles;
	while (tiles)
	{
		if (tiles->tile_index == (id - 1))
		{
			return *tiles;
		}

		tiles = tiles->next;
	}
	throw "The tile does not exist";
}

int TileMap::convertToDoorIndex(int doorIndex) {
	if (doorIndex == 0) return 2; // DOWN
	if (doorIndex == 1) return 1; // RIGHT
	if (doorIndex == 2) return 3; // LEFT
	if (doorIndex == 3) return 0; // UP
}

void TileMap::update(Entity* player, World* world)
{
	_player = player;
	_world = world;
}

void TileMap::loadNextMap()
{
	entityDirections currentDirection = _player->getDirection();
	int doorIndex = convertToDoorIndex(currentDirection);
	bool hasParentNode = _currentNode->_parentNode != nullptr;
	std::vector<int> doorsLocations = _currentNode->_doorsLocation;

	cute_tiled_map_t* oldMapData = _mapData;
	SDL_Texture* oldTexture = _mapTexture;

	if (hasParentNode)
	{
		std::vector<int> nonParentDoors;

		for (auto doors : doorsLocations)
		{
			if (doors != _currentNode->_opposedToParentDoor)
			{
				nonParentDoors.push_back(doors);
			}
		}

		if (_currentNode->_opposedToParentDoor == doorIndex)
		{
			std::cout << "load node: " << _currentNode->_parentNode->_id  << std::endl;
			_world->loadMap(_currentNode->_parentNode);
		}
		else
		{

			if (nonParentDoors.size() == 2)
			{
				if (nonParentDoors[0] == doorIndex)
				{
					std::cout << "load node: " << _currentNode->_rightNode->_id << std::endl;
					_world->loadMap(_currentNode->_rightNode);
				}
				else
				{
					std::cout << "load node: " << _currentNode->_leftNode->_id << std::endl;
					_world->loadMap(_currentNode->_leftNode);
				}
			}
			else
			{
				if (_currentNode->_rightNode != nullptr)
				{
					std::cout << "load node: " << _currentNode->_rightNode->_id << std::endl;
					_world->loadMap(_currentNode->_rightNode);
				}
				else
				{
					std::cout << "load node: " << _currentNode->_leftNode->_id << std::endl;
					_world->loadMap(_currentNode->_leftNode);
				}
			}
		}
	}
	else
	{
		if (doorsLocations[0] == doorIndex)
		{
			std::cout << "load node: " << _currentNode->_rightNode->_id << std::endl;
			_world->loadMap(_currentNode->_rightNode);
		}
		else if (doorsLocations[1] == doorIndex)
		{
			std::cout << "load node: " << _currentNode->_leftNode->_id << std::endl;
			_world->loadMap(_currentNode->_leftNode);
		}
	}

	// re-position player on the map
	switch (_player->getDirection())
	{
		case UP:
			_player->setX(this, 14 * _BLOCK_SIZE);
			_player->setY(this, 15 * _BLOCK_SIZE);
			break;
		case RIGHT:
			_player->setX(this, 1 * _BLOCK_SIZE);
			_player->setY(this, 7 * _BLOCK_SIZE);
			break;
		case DOWN:
			_player->setX(this, 14 * _BLOCK_SIZE);
			_player->setY(this, 1 * _BLOCK_SIZE);
			break;
		case LEFT:
			_player->setX(this, 28 * _BLOCK_SIZE);
			_player->setY(this, 7 * _BLOCK_SIZE);
			break;
	}

	SDL_DestroyTexture(oldTexture);
	cute_tiled_free_map(oldMapData);
}

int TileMap::getMapWidth() const
{
	return _mapWidth;
}

int TileMap::getMapHeight() const
{
	return _mapHeight;
}

int TileMap::getBlockSize() const
{
	return _BLOCK_SIZE;
}