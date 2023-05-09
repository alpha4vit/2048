#include"2048.h"
#include"Button.h"
#include"includes.h"
#include"Background.h"

void drawButton(RenderWindow& window, Button& button);
void drawText(RenderWindow& window, String text, Vector2f position, int number);

int main() {
    RenderWindow menu(VideoMode(1000, 1000), "Main menu");


    //SETTING ICON
    Image icon = *new Image();
    icon.loadFromFile("src\\logo\\logo.png");
    menu.setIcon(427, 427, icon.getPixelsPtr());
    Button button1 = *new Button(*new Vector2f(250, 460));
    Button button2 = *new Button(*new Vector2f(250, 560));
    Button button3 = *new Button(*new Vector2f(250, 660));

    Background bg = *new Background();
    while (menu.isOpen()) {
        Event ev;
        while (menu.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                menu.close();
            }
        }

        menu.clear(Color(255, 255, 255));


        menu.draw(bg.sprite);


        if (Keyboard::isKeyPressed(Keyboard::A)) {
            menu.close();
            showPlayGround();
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (button1.isMouseOver(menu)) {
                menu.close();
                showPlayGround();
            }
        }

        drawButton(menu, button1);
        drawButton(menu, button2);
        drawButton(menu, button3);
        drawText(menu, "Play", button1.getSprite().getPosition(), 1);
        drawText(menu, "Settings", button2.getSprite().getPosition(), 2);
        drawText(menu, "About us", button3.getSprite().getPosition(), 3);


        menu.display();
    }

    return 0;
}



void drawButton(RenderWindow& window, Button& button) {
    if (button.isMouseOver(window)) {
        Image img = Image();
        img.loadFromFile("src\\buttons\\button2.png");
        Texture texture = Texture();
        texture.loadFromImage(img);
        Sprite sprite = Sprite();
        sprite.setTexture(texture);
        sprite.setPosition(button.sprite.getPosition());
        window.draw(sprite);
    }
    else {
        window.draw(button.getSprite());
    }
}

void drawText(RenderWindow& window, String text, Vector2f position, int number) {
    Font font;
    font.loadFromFile("ofont.ru_Bowler.ttf");
    Text text1(text, font, 40);
    text1.setFillColor(Color::White);
    text1.setStyle(sf::Text::Bold);
    switch (number)
    {
    case 1: {text1.setPosition(*new Vector2f(position.x + 180, position.y + 20)); break; }
    case 2: {text1.setPosition(*new Vector2f(position.x + 130, position.y + 20)); break; }
    case 3: {text1.setPosition(*new Vector2f(position.x + 130, position.y + 20)); break; }
    default: break;}
    window.draw(text1);
}
