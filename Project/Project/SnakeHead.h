#pragma once
#include "SnakePart.h"
class SnakeHead: public SnakePart
{
public:
	SnakeHead(float X, float Y, float W, float H) :SnakePart(X, Y, W, H) {
		sprite.setTextureRect(IntRect(4 * W, 0 * H, W, H));
	};
	SnakeHead() {

	};
	void update();
};

