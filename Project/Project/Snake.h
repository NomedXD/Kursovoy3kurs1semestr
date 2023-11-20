#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
using namespace std;
class Snake
{
public:
	float x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir = 0; //����������� (direction) �������� ������
	float currentFrame = 0;
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	list<Sprite> snakeSprites;

	Snake(String F, float X, float Y, float W, float H) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(255, 255, 255));//������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		Sprite headSprite;
		headSprite.setTexture(texture);
		headSprite.setTextureRect(IntRect(0, 270, w, h));
		headSprite.setPosition(X, Y);
		snakeSprites.push_back(headSprite);
		for (list<Sprite>::iterator it = snakeSprites.begin(); it != snakeSprites.end(); ++it) {
			it->setOrigin(w/2, h/2);
		}
		x = X; y = Y;//���������� ��������� �������
	}
public:
	void update(float time);
};

