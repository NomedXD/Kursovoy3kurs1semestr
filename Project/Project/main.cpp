#include "main.h"
using namespace sf;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
HWND initWindow(HINSTANCE instance);
bool checkCollisionWithMap(Snake& snake, const vector<Object>& obj);

bool gameRestart = true;
Level lev;
Font font;
Text score;
vector<Object> obj;
Object snakeHead;
Object snakeInitBody;
Object snakeTail;
SnakeHead head;
SnakeBody body;
SnakeTail tail;
Snake snake;
Apple* apple;
Clock appleClock;
Clock gameTimer;
bool first;
MSG msg;

struct PRNG
{
	std::mt19937 engine;
};
void initGame(PRNG& generator);
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

void menu(HWND hwnd) {
	HMENU hMenu = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, 1, L"Restart game");
	SetMenu(hwnd, hMenu);
}

int main()
{
	SnakePart::init();
	HINSTANCE instance = GetModuleHandle(NULL);

	HWND hwnd = initWindow(instance);
	RenderWindow window(hwnd);
	window.setPosition(sf::Vector2i(100, 0));
	PRNG generator;
	initGenerator(generator);
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (gameRestart) {
				initGame(generator);
				gameRestart = false;
			}
			if (gameTimer.getElapsedTime().asSeconds() >= 0.15f) {
				gameTimer.restart();

				float time = appleClock.getElapsedTime().asMicroseconds();
				appleClock.restart();
				time = time / 1000; 

				if ((first && checkCollisionWithMap(snake, obj)) || snake.checkSnakeSelfCollision() || snake.score == 781) {
					return msg.message = WM_QUIT;
				}

				if (snake.snakeHead.getRect().intersects((*apple).getRect())) {
					snake.score++;
					score.setString("Score: " + to_string(snake.score));
					delete apple;
					apple = generateApple(snake, generator);
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
				(*apple).update(time);
				for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
					it->update();
				}
				snake.snakeTail.update();

				window.clear();
				lev.Draw(window);
				score.setPosition(40,40);
				window.draw(score);
				window.draw((*apple).sprite);
				for (auto it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++) {
					window.draw(it->sprite);
				}
				window.draw(snake.snakeTail.sprite);
				window.draw(snake.snakeHead.sprite);
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
	case WM_CREATE:
	{
		menu(hwnd);
		break;
	}
	case WM_COMMAND: 
	{
		switch (LOWORD(wp))
		{
		case 1: 
		{
			gameRestart = true;
			break;
		}
		default:
			break;
		}
		break;
	}
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
	return CreateWindowEx(WS_EX_WINDOWEDGE, L"Snake", L"Snake", WS_VISIBLE | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 978, 1030, NULL, NULL, instance, NULL);
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

void initGame(PRNG& generator) {
	lev.LoadFromFile("map.tmx");
	font.loadFromFile("fonts/Inkulinati-Regular.otf");
	score = Text("Score: 0", font, 20);
	score.setFillColor(Color::Red);
	score.setStyle(Text::Bold);
	obj = lev.GetObjects("solid");
	snakeHead = lev.GetObject("snakeHead");
	snakeInitBody = lev.GetObject("snakeInitBody");
	snakeTail = lev.GetObject("snakeTail");

	head = SnakeHead(snakeHead.rect.left, snakeHead.rect.top, snakeHead.rect.width, snakeHead.rect.height);
	body = SnakeBody(snakeInitBody.rect.left, snakeInitBody.rect.top, snakeInitBody.rect.width, snakeInitBody.rect.height);
	tail = SnakeTail(snakeTail.rect.left, snakeTail.rect.top, snakeTail.rect.width, snakeTail.rect.height);
	snake = Snake(head, body, tail);
	apple = generateApple(snake, generator);

	gameTimer.restart();

	first = false;
	msg.message = WM_NULL;
}