#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;
class SnakePart
{
public:
	float x, y, w, h, dx, dy, speed = 32;
	int dir = 0; 
	float currentFrame = 0;
	static String File; 
	static Image image;
	static Texture texture;
	Sprite sprite;

	SnakePart(float X, float Y, float W, float H) {  
		w = W; h = H;
		sprite.setTexture(texture);
		x = X; y = Y;
	}
	SnakePart() {};
	static void init();
public:
	virtual void update(float time) = 0;
};

struct turn
{
	float x, y, speed;
	int fromDir, dir;
	bool applied;
	bool beRemoved;
};

