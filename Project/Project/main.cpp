#include "main.h"
using namespace sf;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
HWND initWindow(HINSTANCE instance);
bool checkCollisionWithMap(Snake& snake, const vector<Object>& obj);

struct PRNG
{
	std::mt19937 engine;
};

Apple* generateApple(const Snake& snake, PRNG& generator);

void initGenerator(PRNG& generator)
{
	std::random_device device;
	generator.engine.seed(device());
}

unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
	assert(minValue < maxValue);
	std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
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
	Font font;
	font.loadFromFile("fonts/Inkulinati-Regular.otf");
	Text score("Score: 0", font, 20);
	score.setFillColor(Color::Red);
	score.setStyle(Text::Bold);
	vector<Object> obj;
	obj = lev.GetObjects("solid");
	Object snakeHead = lev.GetObject("snakeHead");
	Object snakeInitBody = lev.GetObject("snakeInitBody");
	Object snakeTail = lev.GetObject("snakeTail");

	SnakeHead head = SnakeHead(snakeHead.rect.left, snakeHead.rect.top, snakeHead.rect.width, snakeHead.rect.height);
	SnakeBody body = SnakeBody(snakeInitBody.rect.left, snakeInitBody.rect.top, snakeInitBody.rect.width, snakeInitBody.rect.height);
	SnakeTail tail = SnakeTail(snakeTail.rect.left, snakeTail.rect.top, snakeTail.rect.width, snakeTail.rect.height);
	Snake snake = Snake(head, body, tail);

	Apple apple = (*generateApple(snake, generator));

	Clock clock;
	Clock gameTimer;
	gameTimer.restart();

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
			if (gameTimer.getElapsedTime().asSeconds() >= 0.15f) {
				gameTimer.restart();

				float time = clock.getElapsedTime().asMicroseconds(); 
				clock.restart(); 
				time = time / 1000; 

				if ((first && checkCollisionWithMap(snake, obj)) || snake.checkSnakeSelfCollision()) {
					return msg.message = WM_QUIT;
				}

				if (snake.snakeHead.getRect().intersects(apple.getRect())) {
					snake.score++;
					score.setString("Score: " + to_string(snake.score));
					//delete &apple;
					apple = (*generateApple(snake, generator));
					// creation of new body
					SnakeBody newBody = SnakeBody(snake.snakeTail.x, snake.snakeTail.y, snake.snakeTail.w, snake.snakeTail.h);
					(newBody).dir = snake.snakeTail.dir;
					(newBody).turns = vector<turn>(snake.snakeTail.turns);
					if (newBody.dir <= 1) {
						newBody.sprite.setTextureRect(IntRect(1 * newBody.w, 0 * newBody.h, newBody.w, newBody.h));
					}
					else
					{
						newBody.sprite.setTextureRect(IntRect(2 * newBody.w, 1 * newBody.h, newBody.w, newBody.h));
					}
					snake.snakeBody.push_back(newBody);
					switch (snake.snakeTail.dir)
					{
					case 0: {
						snake.snakeTail.x -= 32;
						break;
					}
					case 1: {
						snake.snakeTail.x += 32;
						break;
					}
					case 2: {
						snake.snakeTail.y -= 32;
						break;
					}
					case 3: {
						snake.snakeTail.y += 32;
						break;
					}
					default:
						break;
					}
				}

				snake.control();
				snake.snakeHead.update();
				apple.update(time);
				for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
					it->update();
				}
				snake.snakeTail.update();

				window.clear();
				lev.Draw(window);
				score.setPosition(40,40);
				window.draw(score);
				window.draw(apple.sprite);
				for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
					window.draw(it->sprite);
				}
				window.draw(snake.snakeHead.sprite);
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

Apple* generateApple(const Snake& snake, PRNG& generator) {
	bool flag = true;
	int x = 0;
	int y = 0;
	while (flag) {
		x = random(generator, 1, 28);
		y = random(generator, 1, 28);
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
	return  (new Apple(x * 32, y * 32, 32, 32));
}