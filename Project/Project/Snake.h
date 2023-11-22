#pragma once
#include "SnakeHead.h"
#include "SnakeBody.h"
#include "SnakeTail.h"
#include <vector>
#include <windows.h>
using namespace std;
using namespace sf;
class Snake
{
public:
	SnakeHead snakeHead = SnakeHead("snake_sprites_small.png", 320, 320, 32, 32);
	vector<SnakeBody> snakeBody;
	SnakeTail snakeTail = SnakeTail("snake_sprites_small.png", 256, 320, 32, 32);
public:
	Snake() {
		snakeBody.push_back(SnakeBody("snake_sprites_small.png", 288, 320, 32, 32));
	}
	void control();
};