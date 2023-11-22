#include "Snake.h"

void Snake::control() {
	if (GetAsyncKeyState(0x41) && (snakeHead.dir != 1) && !GetAsyncKeyState(0x44) && !GetAsyncKeyState(0x57) && !GetAsyncKeyState(0x53)) {
		int prevDir = snakeHead.dir;
		snakeHead.dir = 1;
		snakeHead.speed = 32;
		snakeHead.sprite.setTextureRect(IntRect(3 * snakeHead.w, 1 * snakeHead.h, snakeHead.w, snakeHead.h));
		for (auto it = snakeBody.begin(); it != snakeBody.end(); it++) {
			it->turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
			it->dir = prevDir;
			it->speed = 32;
		}
		snakeTail.turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
		snakeTail.dir = prevDir;
		snakeTail.speed = 32;
	}
	if (GetAsyncKeyState(0x44) && (snakeHead.dir != 0) && !GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x57) && !GetAsyncKeyState(0x53)) {
		int prevDir = snakeHead.dir;
		snakeHead.dir = 0;
		snakeHead.speed = 32;
		snakeHead.sprite.setTextureRect(IntRect(4 * snakeHead.w, 0 * snakeHead.h, snakeHead.w, snakeHead.h));
		for (auto it = snakeBody.begin(); it != snakeBody.end(); it++) {
			it->turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
			it->dir = prevDir;
			it->speed = 32;
		}
		snakeTail.turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
		snakeTail.dir = prevDir;
		snakeTail.speed = 32;
	}
	if (GetAsyncKeyState(0x57) && (snakeHead.dir != 3) && !GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x44) && !GetAsyncKeyState(0x53)) {
		int prevDir = snakeHead.dir;
		snakeHead.dir = 3;
		snakeHead.speed = 32;
		snakeHead.sprite.setTextureRect(IntRect(3 * snakeHead.w, 0 * snakeHead.h, snakeHead.w, snakeHead.h));
		for (auto it = snakeBody.begin(); it != snakeBody.end(); it++) {
			it->turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
			it->dir = prevDir;
			it->speed = 32;
		}
		snakeTail.turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
		snakeTail.dir = prevDir;
		snakeTail.speed = 32;
	}
	if (GetAsyncKeyState(0x53) && (snakeHead.dir != 2) && !GetAsyncKeyState(0x41) && !GetAsyncKeyState(0x44) && !GetAsyncKeyState(0x57)) {
		int prevDir = snakeHead.dir;
		snakeHead.dir = 2;
		snakeHead.speed = 32;
		snakeHead.sprite.setTextureRect(IntRect(4 * snakeHead.w, 1 * snakeHead.h, snakeHead.w, snakeHead.h));
		for (auto it = snakeBody.begin(); it != snakeBody.end(); it++) {
			it->turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
			it->dir = prevDir;
			it->speed = 32;
		}
		snakeTail.turns.push_back(turn{ snakeHead.x, snakeHead.y, snakeHead.speed, prevDir, snakeHead.dir, false, false });
		snakeTail.dir = prevDir;
		snakeTail.speed = 32;
	}

}