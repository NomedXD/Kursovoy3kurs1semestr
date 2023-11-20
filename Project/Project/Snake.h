#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
using namespace std;
class Snake
{
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	float currentFrame = 0;
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	list<Sprite> snakeSprites;

	Snake(String F, float X, float Y, float W, float H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(255, 255, 255));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		Sprite headSprite;
		headSprite.setTexture(texture);
		headSprite.setTextureRect(IntRect(0, 270, w, h));
		headSprite.setPosition(X, Y);
		snakeSprites.push_back(headSprite);
		for (list<Sprite>::iterator it = snakeSprites.begin(); it != snakeSprites.end(); ++it) {
			it->setOrigin(w/2, h/2);
		}
		x = X; y = Y;//координата появления спрайта
	}
public:
	void update(float time);
};

