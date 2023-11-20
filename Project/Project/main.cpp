#include "main.h"
#include "Snake.h"
using namespace sf;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
HWND initWindow(HINSTANCE instance);
void checkMovementKeysPress(Snake& snake, float time);

int main()
{
	HINSTANCE instance = GetModuleHandle(NULL);

	HWND hwnd = initWindow(instance);
	RenderWindow window(hwnd);

	Texture snakeTexture;
	snakeTexture.loadFromFile("images/snake_sprites_fix.png");

	Snake snake("snakeSprite.jpg", 250, 250, 30, 30);

	Clock clock;
	float currentFrame = 0;

	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее врем€ в микросекундах
			clock.restart(); //перезагружает врем€
			time = time / 1000; //скорость игры


			checkMovementKeysPress(snake, time);
			snake.update(time);
			window.clear();
			window.draw(snake.snakeSprites.front());
			window.display();
		}
	}
	return EXIT_SUCCESS;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		// Quit when we close the main window
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

HWND initWindow(HINSTANCE instance)
{
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hInstance = instance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Snake";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);
	return CreateWindowEx(WS_EX_WINDOWEDGE, L"Snake", L"Snake", WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, instance, NULL);
}

void checkMovementKeysPress(Snake& snake, float time) {
	if (GetAsyncKeyState(0x41)) {
		snake.dir = 1; snake.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движени€. «аметьте - врем€ мы уже здесь ни на что не умножаем и нигде не используем каждый раз
		snake.currentFrame += 0.005 * time;
		if (snake.currentFrame > 6) snake.currentFrame -= 6;
		snake.snakeSprites.front().setTextureRect(IntRect(30 * int(snake.currentFrame), 270, snake.w, snake.h));
	}
	if (GetAsyncKeyState(0x44)) {
		snake.dir = 0; snake.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движени€. «аметьте - врем€ мы уже здесь ни на что не умножаем и нигде не используем каждый раз
		snake.currentFrame += 0.005 * time;
		if (snake.currentFrame > 6) snake.currentFrame -= 6;
		snake.snakeSprites.front().setTextureRect(IntRect(30 * int(snake.currentFrame) + snake.w, 270, -snake.w, snake.h));
	}
	if (GetAsyncKeyState(0x57)) {
		snake.dir = 3; snake.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движени€. «аметьте - врем€ мы уже здесь ни на что не умножаем и нигде не используем каждый раз
		snake.currentFrame += 0.005 * time;
		if (snake.currentFrame > 6) snake.currentFrame -= 6;
		snake.snakeSprites.front().setTextureRect(IntRect(30 * int(snake.currentFrame), 300, snake.w, snake.h));
	}
	if (GetAsyncKeyState(0x53)) {
		snake.dir = 2; snake.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движени€. «аметьте - врем€ мы уже здесь ни на что не умножаем и нигде не используем каждый раз
		snake.currentFrame += 0.005 * time;
		if (snake.currentFrame > 6) snake.currentFrame -= 6;
		snake.snakeSprites.front().setTextureRect(IntRect(30 * int(snake.currentFrame), 300 + snake.h, snake.w, -snake.h));
	}
}