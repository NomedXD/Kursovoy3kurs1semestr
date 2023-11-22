#include "SnakeTail.h"

bool SnakeTail::removeTurnsPredicate(turn currentTurn) {
	return currentTurn.beRemoved == true;
}

void SnakeTail::update(float time) {
	turns.erase(remove_if(turns.begin(), turns.end(), &removeTurnsPredicate), turns.end());
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
			if (it->dir == 0) {
				sprite.setTextureRect(IntRect(4 * w, 2 * h, w, h));
			}
			if (it->dir == 1) {
				sprite.setTextureRect(IntRect(3 * w, 3 * h, w, h));
			}
			if (it->dir == 2) {
				sprite.setTextureRect(IntRect(4 * w, 3 * h, w, h));
			}
			if (it->dir == 3) {
				sprite.setTextureRect(IntRect(3 * w, 2 * h, w, h));
			}
			dir = it->dir;
			speed = it->speed;
			it->applied = true;
			it->beRemoved = true;
		}
	}
}