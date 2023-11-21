#include "SnakeTail.h"

void SnakeTail::update(float time) {
	switch (dir)
	{
	case 0: dx = speed; dy = 0;   break;
	case 1: dx = -speed; dy = 0;   break;
	case 2: dx = 0; dy = speed;   break;
	case 3: dx = 0; dy = -speed;   break;
	}

	x += dx;
	y += dy;

	sprite.setPosition(x, y);
}