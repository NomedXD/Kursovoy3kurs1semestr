#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
using namespace std;
class SnakePart
{
public:
	float x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	float currentFrame = 0;
	static String File; //���� � �����������
	static Image image;//���� �����������
	static Texture texture;//���� ��������
	Sprite sprite;

	SnakePart(float X, float Y, float W, float H) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		w = W; h = H;//������ � ������
		sprite.setTexture(texture);
		x = X; y = Y;//���������� ��������� �������
	}

	static void init();
public:
	virtual void update(float time) = 0;
};

