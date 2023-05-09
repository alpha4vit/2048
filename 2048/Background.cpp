#include "Background.h"

Background::Background()
{
	this->img = Image();
	this->img.loadFromFile("src\\bg\\bg2.jpg");
	this->texture = Texture();
	this->texture.loadFromImage(this->img);
	this->sprite = Sprite();
	this->sprite.setTexture(this->texture);
}
