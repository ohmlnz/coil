#include "Entity.h"

Entity::Entity(InputManager* input = nullptr, GraphicsManager* graphics = nullptr, StateManager* state = nullptr)
	: 
	_input(input),
	_graphics(graphics),
	_state(state)
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
	double posX = getStateManager()->getDirection() == RIGHT ? destX + _width : destX;
	double posY = getStateManager()->getDirection() == DOWN ? destY + _height : destY;

	int tilePosX = std::round(posX) / double(map->getBlockSize());
	int tilePosY = std::round(posY) / double(map->getBlockSize());
	int tileIndex = (tilePosY * (map->getMapWidth() / map->getBlockSize())) + tilePosX;

	// scans for two adjacent tiles ahead of the entity
	int indexes[2];

	if (getStateManager()->getDirection() == RIGHT || getStateManager()->getDirection() == LEFT)
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

void Entity::setPosition(TileMap* map, double x, double y)
{
	if (hasCollided(map, x, getPosition()._y) || hasCollided(map, getPosition()._x, y))
	{
		return;
	}

	_position._x = x;
	_position._y = y;
}

Position Entity::getPosition()
{
	return _position;
}

int Entity::getWidth() {
	return _width;
}

int Entity::getHeight() {
	return _height;
}

Velocity Entity::getVelocity()
{
	return _velocity;
}

void Entity::setVelocity(int velX, int velY)
{
	_velocity._velX = velX;
	_velocity._velY = velY;
}

StateManager* Entity::getStateManager()
{
	if (_state != nullptr)
	{
		return _state;
	}
	
	return nullptr;
}