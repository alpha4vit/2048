#include "Button.h"

Button::Button(Vector2f position)
{
    this->img = Image();
    this->img.loadFromFile("src\\buttons\\button1.png");
    this->texture = Texture();
    this->texture.loadFromImage(this->img);
    this->sprite = Sprite();
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(position);
}

bool Button::isMouseOver(RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > this->sprite.getPosition().x && mousePos.x < this->sprite.getPosition().x + 500
    && mousePos.y > this->sprite.getPosition().y && mousePos.y < this->sprite.getPosition().y+80)
        return true;
    else
        return false;
}






