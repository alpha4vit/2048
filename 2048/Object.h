#pragma once
#include"includes.h"

class Object
{
protected:
	Image img;
	Texture texture;
public:
	Sprite sprite;

	Object(string path, Vector2f position);
	Object();

	bool isMouseOver(RenderWindow& window);
};


