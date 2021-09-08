#pragma once
#include "World.h"
#include <fstream>
#include <iostream>

// TODO: clean up
World::~World() {}

World::World(SDL_Renderer* renderer)
	: 
	_renderer(renderer),
	_player(new Entity(
		new PlayerGraphics({ 32, 32, 50, 50, "assets/sprites/player.json" }, renderer),
		new PlayerState(),
		new PlayerInput()
	))
{
	std::ifstream inputFile("assets/permutations/permutations.json");
	inputFile >> _permutations;

	for (auto entity : _permutations["permutations"]["1"])
	{
		Entity* newEntity;
		entityData data;
		std::string entityLabel = entity;
		std::string entityTexture = _permutations[entityLabel]["texture"];
		data.texture = entityTexture.data();
		data.width = _permutations[entityLabel]["width"];
		data.height = _permutations[entityLabel]["height"];
		data.x = _permutations[entityLabel]["x"];
		data.y = _permutations[entityLabel]["y"];

		if (_permutations[entityLabel]["static"])
		{
			newEntity = new Entity(new PlayerGraphics(data, renderer), nullptr, nullptr);
		}
		else
		{
			newEntity = new Entity(new PlayerGraphics(data, renderer), new PlayerState(), nullptr);
		}

		_entities.push_back(newEntity);
	}

	_tree = new TreeLoader();
	loadMap(_tree->getRootNode());
	// handle text and sound
}

void World::loadMap(Node* node)
{
	_currentNode = node;
	_map = new TileMap(_renderer, _currentNode);
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
	delete map;
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