#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Apple
{
public:
	float x, y, w, h;
	float currentFrame = 0;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Apple(float X, float Y, float W, float H) {
		File = "snake_sprites_small.png";
		image.loadFromFile("images/" + File);
		texture.loadFromImage(image);
		w = W; h = H;
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0 * W, 3 * H, W, H));
		x = X; y = Y;
		sprite.setPosition(x, y);
	}
	void update(float time);
	FloatRect getRect();
};

