#include "main.h"
using namespace sf;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
HWND initWindow(HINSTANCE instance);
bool checkCollisionWithMap(Snake& snake, const vector<Object>& obj);

struct PRNG
{
	std::mt19937 engine;
};

auto_ptr<Apple> generateApple(const Snake& snake, PRNG& generator);

void initGenerator(PRNG& generator)
{
	// Создаём псевдо-устройство для получения случайного зерна.
	std::random_device device;
	// Получаем случайное зерно последовательности
	generator.engine.seed(device());
}

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
	// Проверяем корректность аргументов
	assert(minValue < maxValue);

	// Создаём распределение
	std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

	// Вычисляем псевдослучайное число: вызовем распределение как функцию,
	//  передав генератор произвольных целых чисел как аргумент.
	return distribution(generator.engine);
}

int main()
{
	SnakePart::init();
	HINSTANCE instance = GetModuleHandle(NULL);

	HWND hwnd = initWindow(instance);
	RenderWindow window(hwnd);

	PRNG generator;
	initGenerator(generator);

	Level lev;
	lev.LoadFromFile("map.tmx");
	vector<Object> obj;
	obj = lev.GetObjects("solid");
	Object snakeHead = lev.GetObject("snakeHead");
	Object snakeInitBody = lev.GetObject("snakeInitBody");
	Object snakeTail = lev.GetObject("snakeTail");

	SnakeHead head = SnakeHead(snakeHead.rect.left, snakeHead.rect.top, snakeHead.rect.width, snakeHead.rect.height);
	SnakeBody body = SnakeBody(snakeInitBody.rect.left, snakeInitBody.rect.top, snakeInitBody.rect.width, snakeInitBody.rect.height);
	SnakeTail tail = SnakeTail(snakeTail.rect.left, snakeTail.rect.top, snakeTail.rect.width, snakeTail.rect.height);
	Snake snake = Snake(head, body, tail);

	auto_ptr<Apple> apple = generateApple(snake, generator);

	Clock clock;
	Clock timer;
	timer.restart();

	float currentFrame = 0;
	bool first = false;
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
			if (timer.getElapsedTime().asSeconds() >= 0.15f) {
				cout << timer.getElapsedTime().asSeconds();
				timer.restart();

				float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
				clock.restart(); //перезагружает время
				time = time / 1000; //скорость игры

				if (first && checkCollisionWithMap(snake, obj)) {
					return msg.message = WM_QUIT;
				}

				snake.control();
				snake.snakeHead.update(time);
				apple.get()->update(time);
				for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
					it->update(time);
				}
				snake.snakeTail.update(time);
				//sleep(seconds(0.15));

				window.clear();
				lev.Draw(window);
				window.draw(apple.get()->sprite);
				window.draw(snake.snakeHead.sprite);
				for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
					window.draw(it->sprite);
				}
				window.draw(snake.snakeTail.sprite);
				window.display();

				if (!first) {
					first = true;
				}
			}
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
	return CreateWindowEx(WS_EX_WINDOWEDGE, L"Snake", L"Snake", WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 980, 1000, NULL, NULL, instance, NULL);
}


bool checkCollisionWithMap(Snake& snake, const vector<Object>& obj)
{
	for (int i = 0; i < obj.size(); i++) {
		if (snake.snakeHead.getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				return true;
			}
		}
	}
	return false;
}

auto_ptr<Apple> generateApple(const Snake& snake, PRNG& generator) {
	bool flag = true;
	int x = 0;
	int y = 0;
	while (flag) {
		x = random(generator, 1, 29);
		y = random(generator, 1, 29);
		if ((snake.snakeHead.x != x * snake.snakeHead.w) && (snake.snakeHead.y != y * snake.snakeHead.h)
			&& (snake.snakeTail.x != x * snake.snakeTail.w) && (snake.snakeTail.y != y * snake.snakeTail.h)) {
			flag = false;
			for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
				if ((it->x == (x * it->w)) && (it->y == (y * it->h))) {
					flag = true;
				}
			}
		}
	}
	return auto_ptr<Apple>(new Apple(x * 32, y * 32, 32, 32));
}