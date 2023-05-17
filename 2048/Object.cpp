#include"Object.h"


Object::Object(string path, Vector2f position)
{
    this->img = Image();
    this->img.loadFromFile(path);
    this->texture = Texture();
    this->texture.loadFromImage(this->img);
    this->sprite = Sprite();
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(position);
}


Object::Object()
{
}

bool Object::isMouseOver(RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > this->sprite.getPosition().x && mousePos.x < this->sprite.getPosition().x + 600
        && mousePos.y > this->sprite.getPosition().y && mousePos.y < this->sprite.getPosition().y + 100)
        return true;
    else
        return false;
}


