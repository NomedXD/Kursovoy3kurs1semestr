#pragma once
#include "SnakePart.h"
class SnakeBody: public SnakePart
{
public:
	vector<turn> turns;
public:
	SnakeBody(float X, float Y, float W, float H) :SnakePart(X, Y, W, H) {
		sprite.setTextureRect(IntRect(1 * W, 0 * H, W, H));
	};
	SnakeBody() {};
	void update();
	static bool removeTurnsPredicate(turn currentTurn);
};