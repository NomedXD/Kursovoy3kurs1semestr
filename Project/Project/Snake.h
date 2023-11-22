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
	SnakeHead snakeHead = SnakeHead("snake_sprites_small.png", 250, 250, 32, 32);
	vector<SnakeBody> snakeBody;
	SnakeTail snakeTail = SnakeTail("snake_sprites_small.png", 190, 250, 32, 32);
public:
	Snake() {
		snakeBody.push_back(SnakeBody("snake_sprites_small.png", 220, 250, 32, 32));
	}
	void control();
};