#include "Entity.h"

Entity::Entity(InputManager* input, GraphicsManager* graphics)
	: _input(input),
	_graphics(graphics)
{}

void Entity::update(SDL_Event* event, TileMap* map) {
	if (_input != nullptr)
	{
		_input->update(*this, event);
	}

	if (_graphics != nullptr)
	{
		_graphics->update(*this, map);
	}
}

void Entity::render() {
	if (_graphics != nullptr)
	{
		bool shouldBeAnimated = true;
		_graphics->render(*this, shouldBeAnimated);
	}
}

bool Entity::hasCollided(TileMap* map, double destX, double destY)
{
	// changes the origin of the entity accordingly so it collides properly
	double posX = _currentDirection == RIGHT ? destX + _width : destX;
	double posY = _currentDirection == DOWN ? destY + _height : destY;

	int tilePosX = std::round(posX) / double(map->getBlockSize());
	int tilePosY = std::round(posY) / double(map->getBlockSize());
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
void Entity::setX(TileMap* map, double x) {
	if (hasCollided(map, x, getY()))
	{
		return;
	}

	_x = x;
}

void Entity::setY(TileMap* map, double y) {
	if (hasCollided(map, getX(), y))
	{
		return;
	}

	_y = y;
}

double Entity::getX() {
	return _x;
}

double Entity::getY() {
	return _y;
}

int Entity::getWidth() {
	return _width;
}

int Entity::getHeight() {
	return _height;
}

int Entity::getVelX() {
	return _velX;
}

int Entity::getVelY() {
	return _velY;
}

void Entity::setVelX(int velX) {
	_velX = velX;
}

void Entity::setVelY(int velY) {
	_velY = velY;
}

void Entity::setState(enum entityState newState) {
	_currentState = newState;
}

void Entity::setDirection(enum entityDirections newDirection) {
	_currentDirection = newDirection;
}

entityState Entity::getState() {
	return _currentState;
}

entityDirections Entity::getDirection() {
	return _currentDirection;
}