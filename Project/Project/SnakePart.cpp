#include "SnakePart.h"

String SnakePart::File = "";
Image SnakePart::image{};
Texture SnakePart::texture{};

void SnakePart::init()
{
	File = "snake_sprites_small.png";
	image.loadFromFile("images/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
	image.createMaskFromColor(Color(255, 255, 255));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
	texture.loadFromImage(image);//закидываем наше изображение в текстуру
}