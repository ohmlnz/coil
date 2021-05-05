#pragma once
#include "World.h"
#include "libs/json.h"
#include <fstream>
#include <iostream>

World::~World() {}

World::World(SDL_Renderer* renderer)
	// TODO: to remove - TEST ONLY
	: _renderer(renderer), _testPlayer(new Entity("assets/images/test_sprite.png", renderer))
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
	std::ifstream inputFile(_currentNode->_path);
	nlohmann::json jsonFile;
	inputFile >> jsonFile;

	_map = new TileMap(_renderer, _currentNode);
}

void World::unloadMap(TileMap* map)
{
	delete map;
}

void World::events(SDL_Event* _event)
{
	// TODO: loop through all entities and trigger these events from within

	// SDL converts the stick position into a number between -32768 and 32767. 
	// This deadzone allows us to define a window we can ignore, thus avoiding
	// light taps on the stick.
	const int JOYSTICK_DEAD_ZONE = 8000;

	switch (_event->type)
	{
		case SDL_KEYDOWN:
			switch (_event->key.keysym.scancode)
			{
				case SDL_SCANCODE_UP:
					_testPlayer->velY = -1;
					break;
				case SDL_SCANCODE_LEFT:
					_testPlayer->velX = -1;
					break;
				case SDL_SCANCODE_DOWN:
					_testPlayer->velY = 1;
					break;
				case SDL_SCANCODE_RIGHT:
					_testPlayer->velX = 1;
					break;
			}
			break;
		case SDL_KEYUP:
			_testPlayer->velX = 0;
			_testPlayer->velY = 0;
			break;
		case SDL_JOYAXISMOTION:
			//Motion on controller 0
			if (_event->jaxis.which == 0)
			{
				//X axis motion
				if (_event->jaxis.axis == 0)
				{
					//Left of dead zone
					if (_event->jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						_testPlayer->velX = -1;
					}
					//Right of dead zone
					else if (_event->jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						_testPlayer->velX = 1;
					}
					else
					{
						_testPlayer->velX = 0;
					}
				}
				//Y axis motion
				else if (_event->jaxis.axis == 1)
				{
					//Below of dead zone
					if (_event->jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						_testPlayer->velY = -1;
					}
					//Above of dead zone
					else if (_event->jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						_testPlayer->velY = 1;
					}
					else
					{
						_testPlayer->velY = 0;
					}
				}
			}
			break;
	}
}

void World::render(double lag)
{
	_map->render();
	// TODO: loop through all entities and draw them all
	_testPlayer->draw();
}

void World::update()
{
	_map->update(_testPlayer, this);
	_testPlayer->update();
}