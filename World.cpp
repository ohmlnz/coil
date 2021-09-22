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
	entityData playerData = { 32, 32, 50, 50, "assets/sprites/player.json", false };
	_player = new Entity(new PlayerGraphics(playerData, renderer), new PlayerState(), new PlayerInput());
	_tree = new TreeLoader();
	loadMap(_tree->getRootNode());
	// handle text and sound
}

void World::loadMap(Node* node)
{
	_currentNode = node;
	_map = new TileMap(_renderer, _currentNode);
	loadEntities(_currentNode);
}

void World::loadEntities(Node* node)
{
	std::ifstream inputFile("assets/permutations/permutations.json");
	inputFile >> _permutations;

	// TODO: calculate total nb of permutations dynamically
	std::string random = std::to_string(rand() % 3);
	std::vector<Entity*> entities;

	for (auto entity : _permutations["permutations"][random])
	{
		Entity* newEntity;
		std::string entityLabel = entity;
		std::string textureString = _permutations[entityLabel]["texture"];
		const char* textureChar = textureString.data();

		entityData data = {
			_permutations[entityLabel]["width"],
			_permutations[entityLabel]["height"],
			_permutations[entityLabel]["x"],
			_permutations[entityLabel]["y"],
			textureChar,
			_permutations[entityLabel]["static"],
		};

		if (data.isStatic)
		{
			newEntity = new Entity(new PlayerGraphics(data, _renderer), nullptr, nullptr);
		}
		else
		{
			newEntity = new Entity(new PlayerGraphics(data, _renderer), new PlayerState(), nullptr);
		}

		entities.push_back(newEntity);
	}

	_entities = entities;
}

void World::reloadMap()
{
	Node* oldRoot = _tree->getRootNode();
	TileMap* oldMap = _map;
	_tree->generateNodes();
	_tree->deleteTree(oldRoot);
	loadMap(_tree->getRootNode());
	unloadMap(oldMap);
}

void World::unloadMap(TileMap* map)
{
	for (auto entity : _entities)
	{
		delete entity;
		entity = nullptr;
	}
	delete map;
	map = nullptr;
}

void World::render(double lag)
{
	_map->render();
	_map->animate();
	_player->render();
	for (auto entity : _entities)
	{
		entity->render();
	}
}

void World::update(SDL_Event* event)
{
	_map->update(_player, this);
	_player->update(event, _map);
	for (auto entity : _entities)
	{
		entity->update(event, _map);
	}
}