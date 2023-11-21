#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
using namespace std;
class SnakePart
{
public:
	float x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir = 0; //направление (direction) движения игрока
	float currentFrame = 0;
	static String File; //файл с расширением
	static Image image;//сфмл изображение
	static Texture texture;//сфмл текстура
	Sprite sprite;

	SnakePart(float X, float Y, float W, float H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		w = W; h = H;//высота и ширина
		sprite.setTexture(texture);
		x = X; y = Y;//координата появления спрайта
	}

	static void init();
public:
	virtual void update(float time) = 0;
};

