#pragma once
#include "World.h"
#include "libs/json.h"
#include <fstream>
#include <iostream>

World::~World() {}

World::World(SDL_Renderer* renderer)
	:	_renderer(renderer), 
		// TODO: to remove - TEST ONLY
		_testPlayer(
			new Entity(
				new PlayerInput(),
				new PlayerGraphics("assets/sprites/player.json", renderer)
			)
		)
{
	TreeLoader currentTree;
	loadMap(currentTree.getRootNode());
	// store entities into data structure
	// handle text and sound
}

void World::loadMap(Node* node)
{
	// load assets
	// TODO: add to the assetsmanager singleton
	_currentNode = node;
	//std::ifstream inputFile(_currentNode->_path);
	//nlohmann::json jsonFile;
	//inputFile >> jsonFile;

	_map = new TileMap(_renderer, _currentNode);
}

void World::unloadMap(TileMap* map)
{
	delete map;
}

void World::render(double lag)
{
	_map->render();
	_map->animate();
	// TODO: loop through all entities and draw them all
	_testPlayer->render();
}

void World::update(SDL_Event* event)
{
	//_map->update(_testPlayer, this);
	_testPlayer->update(event, _map);
}