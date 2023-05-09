#pragma once
#include"includes.h"
#include"Object.h"
class Button : public Object
{
private:


	
public:
	Button(Vector2f position);
	bool isMouseOver(RenderWindow& window);

	Sprite getSprite() {
		return this->sprite;
	}

};

