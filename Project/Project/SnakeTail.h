#pragma once
#include "SnakePart.h"
class SnakeTail:public SnakePart
{
public:
	vector<turn> turns;
public:
	SnakeTail(float X, float Y, float W, float H) :SnakePart(X, Y, W, H) {
		sprite.setTextureRect(IntRect(4 * W, 2 * H, W, H));
	};
	SnakeTail() {};
	void update(float time);
	static bool removeTurnsPredicate(turn currentTurn);
};

