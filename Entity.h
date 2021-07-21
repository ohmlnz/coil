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


class Entity
{
public:
	Entity(InputManager* input, GraphicsManager* graphics)
		:	_input(input),
			_graphics(graphics)
	{}

	void update(SDL_Event* event) {
		// TODO: use component pattern to handle:
		// animation - inputs - fight
		if (_input != nullptr)
		{
			_input->update(*this, event);
		}

		if (_graphics != nullptr)
		{
			_graphics->update(*this);
		}
	}

	void render() {
		if (_graphics != nullptr)
		{
			_graphics->render(*this);
		}
	}

	// TODO: create Vector2F class to handle x and y
	void setX(double x) {
		_x = x;
	}

	void setY(double y) {
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
	int _width = 16;
	int _height = 16;
	double _x = 100;
	double _y = 100;
	InputManager* _input;
	GraphicsManager* _graphics;
	// TODO: should decouple into component specific states?
	entityState _currentState = IDLE;
	entityDirections _currentDirection = DOWN;
};