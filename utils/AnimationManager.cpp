#include "AnimationManager.h"

AnimationManager::AnimationManager(int& newId, int& newPosition, SDL_Renderer* renderer, SDL_Texture* world, cute_tiled_tile_descriptor_t& newTile)
{
	id = newId;
	running = true;
	position = newPosition;
	animationFrames = sizeof newTile.animation[0] / sizeof newTile.animation;

	for (int i = 0; i <= animationFrames; i++)
	{
		tileData tile;
		tile.duration = newTile.animation[i].duration;
		tile.tileid = newTile.animation[i].tileid;
		animation.push_back(tile);
	}
}

AnimationManager::~AnimationManager()
{
	running = false;
}

void AnimationManager::animateStatic(SDL_Renderer* renderer, SDL_Texture* world)
{
	// TODO: get all hardcoded values below dynamically
	int tileId = animation[frame].tileid;
	
	int srcX = tileId % 10;
	int srcY = tileId / 10;

	int destX = position % (480 / 16);
	int destY = position / (480 / 16);

	SDL_Rect srcRect = { srcX * 16, srcY * 16, 16, 16 };
	SDL_Rect destRect = { destX * 16, destY * 16, 16, 16 };

	SDL_RenderCopy(renderer, world, &srcRect, &destRect);

	if (maxFrame >= animation[frame].duration) {
		maxFrame = 0;

		if (frame >= animationFrames)
		{
			frame = 0;
		}
		else
		{
			frame++;
		}
	}
	maxFrame += 1;
}

int AnimationManager::getId() const
{
	return id;
}

int AnimationManager::getPosition() const
{
	return position;
}

bool AnimationManager::isAnimationRunning() const
{
	return running;
}