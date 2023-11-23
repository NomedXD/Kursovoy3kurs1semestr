#include "SnakePart.h"

String SnakePart::File = "";
Image SnakePart::image{};
Texture SnakePart::texture{};

void SnakePart::init()
{
	File = "snake_sprites_small.png";
	image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. ¬ нашем случае "hero.png" и получитс€ запись идентична€ 	image.loadFromFile("images/hero/png");
	texture.loadFromImage(image);//закидываем наше изображение в текстуру
}