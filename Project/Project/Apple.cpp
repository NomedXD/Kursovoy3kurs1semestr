#include "Apple.h"

void Apple::update(float time) {
	currentFrame += 0.01 * time;
	if (currentFrame > 3) currentFrame -= 3;
	sprite.setTextureRect(IntRect(w * int(currentFrame), 3 * h, w, h));
}

FloatRect Apple::getRect() {
	return FloatRect(x, y, w, h);
}