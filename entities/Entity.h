#pragma once
#include "../managers/AssetsManager.h"
#include "../managers/InputManager.h"
#include "../managers/GraphicsManager.h"
#include "../managers/StateManager.h"
#include "../utils/TileMap.h"

struct Position
{
	double _x = 100;
	double _y = 100;
};

struct Velocity
{
	int _velX;
	int _velY;
};

class Entity
{
public:
	Entity(InputManager* input, GraphicsManager* graphics, StateManager* state);
	void update(SDL_Event* event, TileMap* map);
	void render();
	bool hasCollided(TileMap* map, double destX, double destY);
	int getWidth();
	int getHeight();
	Position getPosition();
	Velocity getVelocity();
	StateManager* getStateManager();
	void setPosition(TileMap* map, double x, double y);
	void setVelocity(int velX, int velY);
private:
	Position _position;
	Velocity _velocity;
	// TODO: values should come from Tiled's json file
	int _width = 32;
	int _height = 32;
	InputManager* _input;
	GraphicsManager* _graphics;
	StateManager* _state;
	// AIManager
};