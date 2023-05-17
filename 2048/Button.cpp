#include "Button.h"

Button::Button(Vector2f position)
{
    this->img = Image();
    this->img.loadFromFile("src\\buttons\\button5.png"); 
    this->texture = Texture();
    this->texture.loadFromImage(this->img);
    this->sprite = Sprite();
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(position);
}

bool Button::isMouseOver(RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > this->sprite.getPosition().x && mousePos.x < this->sprite.getPosition().x + 400
    && mousePos.y > this->sprite.getPosition().y && mousePos.y < this->sprite.getPosition().y+150)
        return true;
    else
        return false;
}


