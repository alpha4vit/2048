#include "Playground.h"

Playground::Playground(int state)
{
	this->img = Image();
	this->img.loadFromFile("src\\playgrounds\\" + to_string(state)+".png");
	this->texture = Texture();
	this->texture.loadFromImage(this->img);
	this->sprite = Sprite();
	this->sprite.setTexture(this->texture);
}
