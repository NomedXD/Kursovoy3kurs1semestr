#include "SnakePart.h"

String SnakePart::File = "";
Image SnakePart::image{};
Texture SnakePart::texture{};

void SnakePart::init()
{
	File = "snake_sprites_small.png";
	image.loadFromFile("images/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
	texture.loadFromImage(image);//���������� ���� ����������� � ��������
}