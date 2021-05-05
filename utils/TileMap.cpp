#include "TileMap.h"
#define CUTE_TILED_IMPLEMENTATION
#include "../libs/cute_tiled.h"
#define MYNULL NULL
#include <iostream>
#include "../World.h"

TileMap::TileMap(SDL_Renderer* renderer, Node* node)
	: _renderer(renderer), _mapTexture(AssetsManager::loadTexture(node->_texturePath.c_str(), _renderer)), _currentNode(node)
{
	cute_tiled_map_t* loadedMap = cute_tiled_load_map_from_file(node->_assetsPath.c_str(), NULL);
	_mapWidth = (loadedMap->width) * _BLOCK_SIZE;
	_mapHeight = (loadedMap->height) * _BLOCK_SIZE;
	_mapTotalBlocks = (_mapWidth / _BLOCK_SIZE) * (_mapHeight / _BLOCK_SIZE);
	_mapData = loadedMap;
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
			if (i == (_currentNode->_triggerY * (_mapWidth / _BLOCK_SIZE) + _currentNode->_triggerX) 
				&& (_currentNode->_rightNode != nullptr) || (_currentNode->_leftNode != nullptr))
			{
				// TODO: add special tile
				continue;
			}

			if (data[i] > 0)
			{
				if (false) {}
				//if (isTileAnimated(data[i]))
				//{
				//	if (!isAnimationCurrentlyRunning(data[i], i))
				//	{
				//		cute_tiled_tile_descriptor_t tile = getTile(data[i]);
				//		AnimationManager* animatedTile = new AnimationManager(data[i], i, renderer, world, tile);
				//		animatedTiles.push_back(animatedTile);
				//	}
				//}
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
//
//void TileMap::animate()
//{
//	for (auto &tile : animatedTiles)
//	{
//		if (tile->isAnimationRunning())
//		{
//			tile->animateStatic(renderer, world);
//		}
//	}
//}
//
//bool TileMap::isTileCollidable(int id) const
//{
//	cute_tiled_layer_t* layer = map->layers;
//	int tileId;
//
//	while (layer)
//	{
//		// target top layer
//		if (layer->next == nullptr)
//		{
//			tileId = layer->data[id];
//		}
//		layer = layer->next;
//	}
//
//	cute_tiled_tile_descriptor_t* tiles = map->tilesets->tiles;
//	while (tiles)
//	{
//		if (tiles->tile_index == (tileId - 1))
//		{
//			return true;
//		}
//
//		tiles = tiles->next;
//	}
//	return false;
//}
//
//// TODO: why not use tile->isAnimationRunning instead?
//bool TileMap::isAnimationCurrentlyRunning(int id, int position) const
//{
//	for (auto &tile : animatedTiles)
//	{
//		if (tile->getId() == id && tile->getPosition() == position)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool TileMap::isTileAnimated(int id) const
//{
//	cute_tiled_tile_descriptor_t* tiles = map->tilesets->tiles;
//	while (tiles)
//	{
//		if (tiles->tile_index == (id - 1) && tiles->animation != NULL)
//		{
//			return true;
//		}
//
//		tiles = tiles->next;
//	}
//	return false;
//}
//
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

void TileMap::update(Entity* player, World* world)
{
	// TODO: replace by 2dVector
	int playerX = player->getX();
	int playerY = player->getY();


	if ((playerX / _BLOCK_SIZE == _currentNode->_triggerX) && ((playerY / _BLOCK_SIZE) + 1 == _currentNode->_triggerY))
	{
		cute_tiled_map_t* oldMapData = _mapData;
		SDL_Texture* oldTexture = _mapTexture;
		// TODO: figure out which one needs to get loaded
		world->loadMap(_currentNode->_rightNode);
		SDL_DestroyTexture(_mapTexture);
		cute_tiled_free_map(oldMapData);
	}
}