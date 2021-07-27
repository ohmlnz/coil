#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "../libs/cute_tiled.h"
#include <string>
#include <vector>
#include <iostream>

struct tileData {
	int duration;
	int tileid;
};

class AnimationManager
{
public:
	AnimationManager() {};
	AnimationManager(int& newId, int& newPosition, SDL_Renderer* renderer, SDL_Texture* world, cute_tiled_tile_descriptor_t& tile);
	~AnimationManager();
	void animateStatic(SDL_Renderer* renderer, SDL_Texture* world);
	bool isAnimationRunning() const;
	int getId() const;
	int getPosition() const;
	int frame = 1;
	int maxFrame = 0;
private:
	int id;
	int position;
	int animationFrames;
	bool running = false;
	std::vector<struct tileData> animation;
};