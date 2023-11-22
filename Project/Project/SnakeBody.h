#pragma once
#include "SnakePart.h"
class SnakeBody: public SnakePart
{
public:
	vector<turn> turns;
public:
	SnakeBody(String F, float X, float Y, float W, float H) :SnakePart(X, Y, W, H) {
		sprite.setTextureRect(IntRect(1 * W, 0 * H, W, H));
		sprite.setOrigin(W / 2, H / 2);
	};
	void update(float time);
	bool removeTurnsPredicate(turn turn);
};