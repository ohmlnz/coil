#pragma once
#include "../managers/AssetsManager.h"
#include "../managers/InputManager.h"
#include "../managers/GraphicsManager.h"
#include "../utils/TileMap.h"

enum entityState {
	IDLE,
	WALKING,
	RUNNING,
	SHOOTING,
};

enum entityDirections {
	DOWN,
	RIGHT,
	LEFT,
	UP,
};

class Entity
{
public:
	Entity(InputManager* input, GraphicsManager* graphics);
	void update(SDL_Event* event, TileMap* map);
	void render();
	bool hasCollided(TileMap* map, double destX, double destY);
	// TODO: create Vector2F class to handle x and y
	void setX(TileMap* map, double x);
	void setY(TileMap* map, double y);
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	int getVelX();
	int getVelY();
	void setVelX(int velX);
	void setVelY(int velY);
	void setState(enum entityState newState);
	void setDirection(enum entityDirections newDirection);
	entityState getState();
	entityDirections getDirection();
private:
	int _velX, _velY;
	// TODO: values should come from Tiled's json file
	int _width = 32;
	int _height = 32;
	double _x = 100;
	double _y = 100;
	InputManager* _input;
	GraphicsManager* _graphics;
	// TODO: should decouple into component specific states?
	entityState _currentState = IDLE;
	entityDirections _currentDirection = DOWN;
};