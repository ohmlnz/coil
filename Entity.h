#pragma once
#include "utils/AssetsManager.h"
#include "utils/InputManager.h"
#include "utils/GraphicsManager.h"

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

class TileMap;

class Entity
{
public:
	Entity(InputManager* input, GraphicsManager* graphics)
		:	_input(input),
			_graphics(graphics)
	{}

	void update(SDL_Event* event, TileMap* map) {
		if (_input != nullptr)
		{
			_input->update(*this, event);
		}

		if (_graphics != nullptr)
		{
			_graphics->update(*this, map);
		}
	}

	void render() {
		if (_graphics != nullptr)
		{
			bool shouldBeAnimated = true;
			_graphics->render(*this, shouldBeAnimated);
		}
	}

	bool hasCollided(TileMap* map, double destX, double destY)
	{
		// changes the origin of the entity accordingly so it collides properly
		double posX = _currentDirection == RIGHT ? destX + _width : destX;
		double posY = _currentDirection == DOWN ? destY + _height : destY;

		int tilePosX = std::round(posX) / double(map->getBlockSize());
		int tilePosY = std::round(posY)/ double(map->getBlockSize());
		int tileIndex = (tilePosY * (map->getMapWidth() / map->getBlockSize())) + tilePosX;

		// scans for two adjacent tiles ahead of the entity
		int indexes[2];

		if (_currentDirection == RIGHT || _currentDirection == LEFT)
		{
			indexes[0] = tileIndex;
			indexes[1] = ((tilePosY + 1) * (map->getMapWidth() / map->getBlockSize())) + tilePosX;
		}
		else
		{
			indexes[0] = tileIndex;
			indexes[1] = (tilePosY * (map->getMapWidth() / map->getBlockSize())) + tilePosX + 1;
		}

		if (map->isTileCollidable(indexes))
		{
			return true;
		}

		return false;
	}

	// TODO: create Vector2F class to handle x and y
	void setX(TileMap* map, double x) {
		if (hasCollided(map, x, getY()))
		{
			return;
		}

		_x = x;
	}

	void setY(TileMap* map, double y) {
		if (hasCollided(map, getX(), y))
		{
			return;
		}

		_y = y;
	}

	double getX() {
		return _x;
	}

	double getY() {
		return _y;
	}

	int getWidth() {
		return _width;
	}

	int getHeight() {
		return _height;
	}

	int getVelX() {
		return _velX;
	}

	int getVelY() {
		return _velY;
	}

	void setVelX(int velX) {
		_velX = velX;
	}

	void setVelY(int velY) {
		_velY = velY;
	}

	void setState(enum entityState newState) {
		_currentState = newState;
	}

	void setDirection(enum entityDirections newDirection) {
		_currentDirection = newDirection;
	}

	entityState getState() {
		return _currentState;
	}

	entityDirections getDirection() {
		return _currentDirection;
	}

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