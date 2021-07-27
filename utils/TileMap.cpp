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
	while (tiles)
	{
		if (tiles->tile_index == (tilesIds[0] - 1) || tiles->tile_index == (tilesIds[1] - 1))
		{
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

struct doorCoordinates
{
	int x;
	int y;
};

struct doorCoordinates getDoorIndex(int doorIndex) {
	if (doorIndex == 0)
	{
		return doorCoordinates{ 14, 0 };
	}
	else if (doorIndex == 1)
	{
		return doorCoordinates{ 29, 7 };
	}
	else if (doorIndex == 2)
	{
		return doorCoordinates{ 14, 16 };
	}
	else if (doorIndex == 3)
	{
		return doorCoordinates{ 0, 7 };
	}
}

void TileMap::deleteOldMapData()
{
	cute_tiled_map_t* oldMapData = _mapData;
	SDL_Texture* oldTexture = _mapTexture;
	SDL_DestroyTexture(oldTexture);
	cute_tiled_free_map(oldMapData);
}

//void TileMap::update(Entity* player, World* world)
//{
	// TODO: turn map detection into method
	// TODO: replace by 2dVector
	//int pX = player->getX();
	//int pY = player->getY();
	//int pHeight = player->getHeight();
	//int pWidth = player->getWidth();
	//int nbOfDoors = _currentNode->_doorsLocation.size();

	//for (auto doorIndex : _currentNode->_doorsLocation)
	//{
	//	doorCoordinates doorCoordinates = getDoorIndex(doorIndex);

	//	// TODO: improve detection of tiles
	//	// should perhaps translate the x,y coordinate of the texture?
	//	if (doorCoordinates.x == (pX / _BLOCK_SIZE) && doorCoordinates.y == (pY / _BLOCK_SIZE) )
	//	{
	//		if (doorIndex == _currentNode->_opposedToParentDoor)
	//		{
	//			world->loadMap(_currentNode->_parentNode);
	//		}
	//		else
	//		{
	//			std::vector<int> filtered;
	//			for (auto doorIndex : _currentNode->_doorsLocation)
	//			{
	//				if (doorIndex != _currentNode->_opposedToParentDoor)
	//				{
	//					filtered.push_back(doorIndex);
	//				}
	//			}

	//			if (filtered.size() == 1)
	//			{
	//				if (_currentNode->_rightNode != nullptr)
	//				{
	//					world->loadMap(_currentNode->_rightNode);
	//				}
	//				else
	//				{
	//					world->loadMap(_currentNode->_leftNode);
	//				}
	//			}
	//			else
	//			{
	//				if (doorIndex == filtered[0])
	//				{
	//					world->loadMap(_currentNode->_rightNode);
	//				}
	//				else
	//				{
	//					world->loadMap(_currentNode->_leftNode);
	//				}
	//			}

	//		}

	//		deleteOldMapData();


	//		if (doorCoordinates.x == 0)
	//		{
	//			player->setX(27 * _BLOCK_SIZE);
	//		}
	//		else if (doorCoordinates.x == 29)
	//		{
	//			player->setX(2 * _BLOCK_SIZE);
	//		}
	//		else if (doorCoordinates.y == 0)
	//		{
	//			player->setY(14 * _BLOCK_SIZE);
	//		}
	//		else
	//		{
	//			player->setY(2 * _BLOCK_SIZE);
	//		}

	//	}
	//}
//}

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