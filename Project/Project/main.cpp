#include "main.h"
#include "Snake.h"
using namespace sf;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
HWND initWindow(HINSTANCE instance);
void checkMovementKeysPress(Snake& snake, float time);

int main()
{
	SnakePart::init();
	HINSTANCE instance = GetModuleHandle(NULL);

	HWND hwnd = initWindow(instance);
	RenderWindow window(hwnd);

	Snake snake;

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
			float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
			clock.restart(); //������������� �����
			time = time / 1000; //�������� ����


			checkMovementKeysPress(snake, time);
			snake.snakeHead.update(time);
			for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
				it->update(time);
			}
			snake.snakeTail.update(time);


			window.clear();
			window.draw(snake.snakeHead.sprite);
			for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
				window.draw(it->sprite);
			}
			window.draw(snake.snakeTail.sprite);
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
		snake.snakeHead.dir = 1;
		snake.snakeHead.speed = 0.2;
		
	}
	if (GetAsyncKeyState(0x44)) {
		snake.snakeHead.dir = 0;
		snake.snakeHead.speed = 0.2;
		
	}
	if (GetAsyncKeyState(0x57)) {
		snake.snakeHead.dir = 3;
		snake.snakeHead.speed = 0.2;
		
	}
	if (GetAsyncKeyState(0x53)) {
		snake.snakeHead.dir = 2;
		snake.snakeHead.speed = 0.2;
	}
}