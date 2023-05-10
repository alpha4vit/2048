#pragma once
#include"2048.h"
#include"Button.h"
#include"includes.h"
#include"Background.h"

void MainMenu();
void drawText(RenderWindow& window, String text, Vector2f position, int number);
void readResults(int& LAST_RESULT, int& BEST_RESULT);

int main() {
    MainMenu();
}


void MainMenu() {
    RenderWindow menu(VideoMode(1000, 1000), "Main menu");
    int LAST_RESULT;
    int BEST_RESULT;
    readResults(LAST_RESULT, BEST_RESULT);
    //SETTING ICON`
    Image icon = *new Image();
    icon.loadFromFile("src\\logo\\logo.png");
    menu.setIcon(427, 427, icon.getPixelsPtr());
    Button buttonPlay = *new Button(*new Vector2f(250, 460));
    Button buttonSettings = *new Button(*new Vector2f(250, 560));
    Button buttonAboutUs = *new Button(*new Vector2f(250, 660));

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
            
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (buttonPlay.isMouseOver(menu)) {
                menu.close();
                play();
            }
        }

        drawButton(menu, buttonPlay);
        drawButton(menu, buttonSettings);
        drawButton(menu, buttonAboutUs);
        drawText(menu, "Play", buttonPlay.getSprite().getPosition(), 1);
        drawText(menu, "Settings", buttonSettings.getSprite().getPosition(), 2);
        drawText(menu, "About us", buttonAboutUs.getSprite().getPosition(), 3);
        drawText(menu, to_string(LAST_RESULT), *new Vector2f(100, 100), 0);
        drawText(menu, to_string(BEST_RESULT), *new Vector2f(200, 100), 0);

        menu.display();
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
    case 0: {text1.setPosition(position); break; }
    case 1: {text1.setPosition(*new Vector2f(position.x + 180, position.y + 20)); break; }
    case 2: {text1.setPosition(*new Vector2f(position.x + 130, position.y + 20)); break; }
    case 3: {text1.setPosition(*new Vector2f(position.x + 130, position.y + 20)); break; }
    default: break;
    }
    window.draw(text1);
}


void readResults(int& LAST_RESULT, int& BEST_RESULT) {
    fstream file;
    file.open("result.txt");
    file >> LAST_RESULT;
    file >> BEST_RESULT;
    file.close();
}