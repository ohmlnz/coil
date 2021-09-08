#pragma once
#include "../managers/AssetsManager.h"
#include "../managers/InputManager.h"
#include "../managers/GraphicsManager.h"
#include "../managers/StateManager.h"
#include "../utils/TileMap.h"

struct Position
{
	double _x;
	double _y;
};

struct Velocity
{
	int _velX;
	int _velY;
};

struct Dimensions
{
	int _width;
	int _height;
};

class Entity
{
public:
	Entity(GraphicsManager* graphics, StateManager* state, InputManager* input);
	void update(SDL_Event* event, TileMap* map);
	void render();
	bool hasCollided(TileMap* map, double destX, double destY);
	Dimensions getDimensions();
	Position getPosition();
	Velocity getVelocity();
	StateManager* getStateManager();
	void setDimensions(int width, int height);
	void setPosition(TileMap* map, double x, double y);
	void setVelocity(int velX, int velY);
private:
	Position _position;
	Velocity _velocity;
	Dimensions _dimensions;
	InputManager* _input;
	GraphicsManager* _graphics;
	StateManager* _state;
	bool _shouldBeAnimated;
};