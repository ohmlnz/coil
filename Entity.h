#pragma once

class Entity
{
public:
	void draw(SDL_Renderer* renderer) {
		SDL_Rect r;
		r.x = _x;
		r.y = _y;
		r.w = 50;
		r.h = 50;

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

		SDL_RenderFillRect(renderer, &r);
	}

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

private:
	double _x = 50;
	double _y = 50;
};