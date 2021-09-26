#pragma once
#include "World.h"
#include "utils/TileMap.h"
#include <fstream>

// TODO: clean up
World::~World() {}

World::World(SDL_Renderer* renderer)
	: 
	_renderer(renderer)
{
	// TODO: create a utility method
	srand(time(NULL));
	entityData* playerData = new entityData({ 32, 32, 50, 50, "assets/sprites/player.json", false });
	_player = new Entity(new PlayerGraphics(playerData, _renderer), new PlayerState(), new PlayerInput());
	_tree = new TreeLoader();
	loadMap(_tree->getRootNode());
	// handle text and sound
}

void World::loadMap(Node* node)
{
	if (_map != nullptr)
	{
		if (!_entities.empty())
		{
			for (auto entity : _entities)
			{
				delete entity;
				entity = nullptr;
			}

			_entities = std::vector<Entity*>{};
		}

		_exitDirection = _player->getStateManager()->getDirection();

		delete _player;
		_player = nullptr;
	}
	_currentNode = node;
	TileMap* newMap = new TileMap(_renderer, _currentNode);
	delete _map;
	_map = newMap;
	loadEntities(_currentNode);
}

void World::loadEntities(Node* node)
{
	if (node->_entitiesData.empty())
	{
		std::ifstream inputFile("assets/permutations/permutations.json");
		inputFile >> _permutations;

		// TODO: calculate total nb of permutations dynamically
		std::string random = std::to_string(rand() % 3);

		for (auto entity : _permutations["permutations"][random])
		{
			Entity* newEntity = nullptr;
			std::string entityLabel = entity;

			entityData* data = new entityData({
				_permutations[entityLabel]["width"],
				_permutations[entityLabel]["height"],
				_permutations[entityLabel]["x"],
				_permutations[entityLabel]["y"],
				_permutations[entityLabel]["texture"],
				_permutations[entityLabel]["static"],
			});

			node->_entitiesData.push_back(data);

			if (data->isStatic)
			{
				newEntity = new Entity(new PlayerGraphics(data, _renderer), nullptr, nullptr);
			}
			else
			{
				newEntity = new Entity(new PlayerGraphics(data, _renderer), new PlayerState(), nullptr);
			}

			_entities.push_back(newEntity);
		}
	}
	else
	{
		for (auto data : node->_entitiesData)
		{
			Entity* newEntity = nullptr;

			if (data->isStatic)
			{
				newEntity = new Entity(new PlayerGraphics(data, _renderer), nullptr, nullptr);
			}
			else
			{
				newEntity = new Entity(new PlayerGraphics(data, _renderer), new PlayerState(), nullptr);
			}

			_entities.push_back(newEntity);
		}
	}

	double x;
	double y;

	switch (_exitDirection)
	{
		case UP:
			x = 14 * _map->getBlockSize();
			y = 15 * _map->getBlockSize();
			break;
		case RIGHT:
			x = 1 * _map->getBlockSize();
			y = 7 * _map->getBlockSize();
			break;
		case DOWN:
			x = 14 * _map->getBlockSize();
			y = 1 * _map->getBlockSize();
			break;
		case LEFT:
			x = 28 * _map->getBlockSize();
			y = 7 * _map->getBlockSize();
			break;
	}

	entityData* playerData = new entityData({ 32, 32, x, y, "assets/sprites/player.json", false });
	_player = new Entity(new PlayerGraphics(playerData, _renderer), new PlayerState(), new PlayerInput());
}

void World::render(double lag)
{
	if (_map != nullptr && !_map->isLoadingMap)
	{
		_map->render();
		_map->animate();

		if (!_entities.empty())
		{
			for (auto entity : _entities)
			{
				entity->render();
			}
		}

		_player->render();
	}
}

void World::update(SDL_Event* event)
{
	if (_map != nullptr && !_map->isLoadingMap)
	{
		_map->update(_player, this);

		if (!_entities.empty())
		{
			for (auto entity : _entities)
			{
				entity->update(event, _map);
			}
		}

		_player->update(event, _map);
	}
}