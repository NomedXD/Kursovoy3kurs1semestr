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
	SnakeHead snakeHead;
	vector<SnakeBody> snakeBody;
	SnakeTail snakeTail;
	int score = 0;
public:
	Snake(SnakeHead& head, SnakeBody& body, SnakeTail& tail) {
		snakeHead = head;
		snakeBody.push_back(body);
		snakeTail = tail;
	}
	Snake() {};
	void control();
	bool checkSnakeSelfCollision();
};