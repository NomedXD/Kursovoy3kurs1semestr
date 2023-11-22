#include "SnakeBody.h"

bool SnakeBody::removeTurnsPredicate(turn turn) {
	return turn.beRemoved == true;
}

void SnakeBody::update(float time) {
	turns.erase(remove_if(turns.begin(), turns.end(), &SnakeBody::removeTurnsPredicate), turns.end());
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

	for (auto it = turns.begin(); it != turns.end(); it++) {
		if ((it->x == x) && (it->y == y) && (it->applied == false)) {
			if ((it->fromDir == 1) && (it->dir == 3)) {
				sprite.setTextureRect(IntRect(0 * w, 1 * h, w, h));
			}
			if ((it->fromDir == 0) && (it->dir == 3)) {
				sprite.setTextureRect(IntRect(2 * w, 2 * h, w, h));
			}
			if ((it->fromDir == 1) && (it->dir == 2)) {
				sprite.setTextureRect(IntRect(0 * w, 0 * h, w, h));
			}
			if ((it->fromDir == 0) && (it->dir == 2)) {
				sprite.setTextureRect(IntRect(2 * w, 0 * h, w, h));
			}
			dir = it->dir;
			speed = it->speed;
			it->applied = true;
		}
		if (it->applied == true) {
			if ((dir == 0) || (dir == 1)) {
				sprite.setTextureRect(IntRect(1 * w, 0 * h, w, h));
			}
			else
			{
				sprite.setTextureRect(IntRect(2 * w, 1 * h, w, h));
			}
			it->beRemoved = true;
		}
	}
	
}