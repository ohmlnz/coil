#pragma once

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

class StateManager
{
public:
	virtual ~StateManager() {}

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
	entityState _currentState = IDLE;
	entityDirections _currentDirection = DOWN;
};
