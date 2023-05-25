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

bool Object::isMouseOver(RenderWindow& window, int state)
{
    int xSize = 600;
    int ySize = 160;
    switch (state)
    {
    case 1: {
        xSize = 250;
        ySize = 76; break;
    }
    case 2: {
        ySize = 125;
        xSize = 125; break;
    }
    case 3: {
        xSize = 80;
        ySize = 80; break;
    }
    default:
        break;
    }
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > this->sprite.getPosition().x && mousePos.x < this->sprite.getPosition().x + xSize
        && mousePos.y > this->sprite.getPosition().y && mousePos.y < this->sprite.getPosition().y + ySize)
        return true;
    else
        return false;
}


