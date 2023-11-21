#pragma once
#include "SnakePart.h"
class SnakeTail:public SnakePart
{
public:
	SnakeTail(String F, float X, float Y, float W, float H) :SnakePart(X, Y, W, H) {
		sprite.setTextureRect(IntRect(4 * W, 2 * H, W, H));
	};
	void update(float time);
};

