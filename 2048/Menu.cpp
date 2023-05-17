#pragma once

#include"Button.h"
#include"includes.h"
#include"move.h"
#include"Nums.h"
#include<SFML/Audio/Music.hpp>
#include"KeyChecker.h"

void option(Music& music);
void MainMenu(Music& music);
void settings(Music& music);
int play(Music& music, int state);
void drawText(RenderWindow& window, String text, Vector2f position, int number, bool isMouseOver);
void readResults(int& LAST_RESULT, int& BEST_RESULT);
int readVolumeFromFile();
Vector2i getMousePosition(RenderWindow& window, Vector2i position);
int convertFromPositionToVolume(Vector2i position);
Vector2f convertFromVolumeToPosition(int volume, Object sliderLine);
void writeVolumeToFile(int volume);
void drawBar(RenderWindow& window, vector<int> num, int state);
void drawPlayGround(RenderWindow& window, int state);
void drawButton(RenderWindow& window, Button& button);
void showCurrentResult(RenderWindow& window, int CURRENT_RESULT);
void writeToFileResults(int LAST_RESULT);


int main() {
    Music music;
    music.openFromFile("src\\sounds\\backsound.ogg");
    music.play();
    music.setLoop(true);
    int volume = readVolumeFromFile();
    cout << volume;
    music.setVolume(volume);
    MainMenu(music);
}


void MainMenu(Music& music) {

    RenderWindow menu(VideoMode(1000, 1000), "Main menu");
    int LAST_RESULT;
    int BEST_RESULT;
    readResults(LAST_RESULT, BEST_RESULT);
    bool showOption = false;
    //SETTING ICON
    Image icon = *new Image();
    icon.loadFromFile("src\\logo\\logo.png");
    menu.setIcon(427, 427, icon.getPixelsPtr());
    Button buttonPlay = *new Button(*new Vector2f(300, 500));
    Button buttonSettings = *new Button(*new Vector2f(300, 665));
    Button buttonAboutUs = *new Button(*new Vector2f(300, 820));
    Object bg = *new Object("src\\bg\\bg2.jpg", *new Vector2f(0, 0));

    while (menu.isOpen()) {
        Event ev;
        while (menu.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                menu.close();
            }
        }

        menu.clear(Color(255, 255, 255));


        menu.draw(bg.sprite);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (buttonPlay.isMouseOver(menu)) {
                showOption = true;
            }
            else if (buttonSettings.isMouseOver(menu)) {
                menu.close();
                settings(music);
            }
            else {
                showOption = false;
            }
        }


        drawButton(menu, buttonPlay);
        drawButton(menu, buttonSettings);
        drawButton(menu, buttonAboutUs);
        drawText(menu, "Play", buttonPlay.getSprite().getPosition(), 1, buttonPlay.isMouseOver(menu));
        drawText(menu, "Settings", buttonSettings.getSprite().getPosition(), 2, buttonSettings.isMouseOver(menu));
        drawText(menu, "About us", buttonAboutUs.getSprite().getPosition(), 3, buttonAboutUs.isMouseOver(menu));
        drawText(menu, to_string(LAST_RESULT), *new Vector2f(100, 100), 0, false);
        drawText(menu, to_string(BEST_RESULT), *new Vector2f(200, 100), 0, false);


        if (showOption) {
            Object x3 = *new Object("src\\buttons\\buttonOption.png", *new Vector2f(380, 100));
            Object x4 = *new Object("src\\buttons\\buttonOption.png", *new Vector2f(380, 160));
            Object x5 = *new Object("src\\buttons\\buttonOption.png", *new Vector2f(380, 220));
            menu.draw(x3.sprite);
            menu.draw(x4.sprite);
            menu.draw(x5.sprite);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (x3.isMouseOver(menu)) {
                    menu.close();
                    play(music, 3);
                }
                else if (x4.isMouseOver(menu)) {
                    menu.close();
                    play(music, 4);
                }
                else if (x5.isMouseOver(menu)) {
                    menu.close();
                    play(music, 5);
                }

            }

        }
        menu.display();
    }
}

void option(Music& music) {
    RenderWindow option(VideoMode(300, 200), "option", Style::None);
    while (option.isOpen()) {
        Event ev;
        while (option.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                option.close();
            }
        }

        option.clear(Color(255, 255, 255));

        option.display();
    }
}

void settings(Music& music) {
    RenderWindow settings(VideoMode(1000, 1000), "Settings");
    
    int volume = readVolumeFromFile();
    if (volume < 0 || volume > 100) {
        volume = 50;
    }
    

    //SETTING ICON
    Image icon = *new Image();
    icon.loadFromFile("src\\logo\\logo.png");
    settings.setIcon(427, 427, icon.getPixelsPtr());
    Object bg = *new Object("src\\bg\\bg2.jpg", *new Vector2f(0, 0));
    Object sliderLine = *new Object("src\\sliders\\line.png", *new Vector2f(150, 200));
    Object slider = *new Object("src\\sliders\\slider.png", convertFromVolumeToPosition(volume, sliderLine));
    Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(770, 40));
    while (settings.isOpen()) {
        Event ev;
        while (settings.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                settings.close();
            }
        }

        settings.clear(Color(255, 255, 255));

        settings.draw(bg.sprite);
        settings.draw(buttonExit.sprite);
        drawText(settings, "SETTINGS", *new Vector2f(400, 50), 0, false);
        settings.draw(sliderLine.sprite);
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mouseCoord = getMousePosition(settings, Mouse::getPosition());
            if (sliderLine.isMouseOver(settings)) {
                slider.sprite.setPosition(mouseCoord.x, sliderLine.sprite.getPosition().y-18);
                volume = convertFromPositionToVolume(mouseCoord);
                music.setVolume(volume);
            }
            else if (buttonExit.isMouseOver(settings)) {
                settings.close();
                MainMenu(music);
            }
        }
        settings.draw(slider.sprite);
        settings.display();
    }
    cout << endl << volume<< endl;
    writeVolumeToFile(volume);
    cout << endl << volume << endl;
}


int play(Music& music, int state)
{
    
    RenderWindow game(VideoMode(1000, 1000), "Game");
    
    Object bg = *new Object("src\\bg\\bg2.jpg", *new Vector2f(0, 0));
    Object buttonRestart = *new Object("src\\buttons\\restart.png", *new Vector2f(870, 40));
    Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(770, 40));
    Object upArrow = *new Object("src\\buttons\\upArrow.png", *new Vector2f(450, 670));
    Object downArrow = *new Object("src\\buttons\\downArrow1.png", *new Vector2f(450, 800));
    Object leftArrow = *new Object("src\\buttons\\leftArrow1.png", *new Vector2f(320, 735));
    Object rightArrow = *new Object("src\\buttons\\rightArrow1.png", *new Vector2f(580, 735));

    bool buttonPressed = false;
    bool keyPressed = false;
    double tempTime;
    int CURRENT_RESULT = 0;
    vector<vector<vector<int>>> nums = genNums(state);
    genFnum(nums);

    //SETTING ICON
    Image icon = *new Image();
    icon.loadFromFile("src\\logo\\logo.png");
    game.setIcon(427, 427, icon.getPixelsPtr());


    

    while (game.isOpen()) {
        Event ev;
        while (game.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                game.close();
            }
        }
        game.clear(Color(255, 255, 255));
        game.draw(bg.sprite);
        game.draw(buttonRestart.sprite);
        game.draw(buttonExit.sprite);
        game.draw(downArrow.sprite);
        game.draw(upArrow.sprite);
        game.draw(leftArrow.sprite);
        game.draw(rightArrow.sprite);
        drawPlayGround(game, state);


        for (int i = 0; i < size(nums); ++i) {
            for (int j = 0; j < size(nums[i]); ++j) {
                if (nums[i][j][0] != 0) {
                    drawBar(game, nums[i][j], state);
                }
            }
        }

        if (ev.type == Event::MouseButtonReleased && ev.mouseButton.button == Mouse::Left) {
            buttonPressed = false;
        }
        if (ev.type == Event::KeyReleased && (ev.key.code == Keyboard::W || ev.key.code == Keyboard::S || ev.key.code == Keyboard::D || ev.key.code == Keyboard::A)) {
        
            keyPressed = false;
        }


        if (!keyPressed){
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                MoveRight(nums, CURRENT_RESULT); keyPressed = true;
                newRandNum(nums);
            }
            else if (Keyboard::isKeyPressed(Keyboard::A)) {
                tempTime = time(NULL); keyPressed = true;
                MoveLeft(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
            else if (Keyboard::isKeyPressed(Keyboard::S)) {
                tempTime = time(NULL); keyPressed = true;
                MoveDown(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
            else if (Keyboard::isKeyPressed(Keyboard::W)) {
                tempTime = time(NULL); keyPressed = true;
                MoveUp(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
           
        }

        if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed) {
            buttonPressed = true;
            if (buttonRestart.isMouseOver(game)) {
                game.close();
                play(music, state);
            }
            else if (buttonExit.isMouseOver(game)) {
                game.close();
                writeToFileResults(CURRENT_RESULT);
                MainMenu(music);

            }
            else if (upArrow.isMouseOver(game)) {
                MoveUp(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
            else if (leftArrow.isMouseOver(game)) {
                MoveLeft(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
            else if (rightArrow.isMouseOver(game)) {
                MoveRight(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
            else if (downArrow.isMouseOver(game)) {
                MoveDown(nums, CURRENT_RESULT);
                newRandNum(nums);
            }
        }

        showCurrentResult(game, CURRENT_RESULT);

        game.display();
    }

    return CURRENT_RESULT;
}


void drawBar(RenderWindow& window, vector<int> num, int state) {
    Image img = Image();
    img.loadFromFile("src\\" + to_string(state) + "\\" + to_string(num[0]) + ".png");
    Texture texture = Texture();
    texture.loadFromImage(img);
    Sprite sprite = Sprite();
    sprite.setTexture(texture);
    sprite.setPosition(*new Vector2f(num[1], num[2]));
    window.draw(sprite);
}

void drawPlayGround(RenderWindow& window, int state) {
    RectangleShape rect;
    rect.setFillColor(Color::White);
    rect.setPosition(*new Vector2f(35, 35));
    rect.setSize(*new Vector2f(605, 605));
    window.draw(rect);
}

void showCurrentResult(RenderWindow& window, int CURRENT_RESULT) {
    Font font;
    font.loadFromFile("ofont.ru_Bowler.ttf");


    Text number(to_string(CURRENT_RESULT), font, 40);
    number.setFillColor(Color::Black);
    number.setStyle(sf::Text::Bold);
    number.setPosition(*new Vector2f(850, 220));

    Text text("YOUR SCORE:", font, 25);
    text.setFillColor(Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(*new Vector2f(770, 185));

    window.draw(number);
    window.draw(text);
}

void drawButton(RenderWindow& window, Button& button) {
    if (button.isMouseOver(window)) {
        Image img = Image();
        img.loadFromFile("src\\buttons\\button4.png");
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



void writeToFileResults(int LAST_RESULT) {
    fstream file;
    file.open("result.txt");
    int BEST_RESULT;
    file >> BEST_RESULT;
    file >> BEST_RESULT;
    file.close();
    if (BEST_RESULT < LAST_RESULT)
        BEST_RESULT = LAST_RESULT;
    ofstream fout;
    fout.open("result.txt");
    fout.clear();
    fout << LAST_RESULT << "\n" << BEST_RESULT;
    fout.close();
}

void writeVolumeToFile(int volume) {
    ofstream file;
    file.open("properties.txt");
    file.clear();
    file << volume;
    file.close();
}

int readVolumeFromFile() {
    int temp;
    fstream file;
    file.open("properties.txt");
    file >> temp;
    file.close();
    return temp;
}


Vector2i getMousePosition(RenderWindow& window, Vector2i position) {
    return position - window.getPosition();
}

int convertFromPositionToVolume(Vector2i position) {
    int x = position.x - 150;
    return x / 6.5;
}

Vector2f convertFromVolumeToPosition(int volume, Object sliderLine) {
    return *new Vector2f(volume * 6.5 + 150, sliderLine.sprite.getPosition().y - 18);
}



void drawText(RenderWindow& window, String text, Vector2f position, int number, bool isMouseOver) {
    Font font;
    font.loadFromFile("ofont.ru_Bowler.ttf");
    Text text1(text, font, 40);
    if (!isMouseOver)
        text1.setFillColor(Color::White);
    else
        text1.setFillColor(Color(117, 117, 117));
    text1.setStyle(sf::Text::Bold);
    switch (number)
    {
    case 0: {text1.setPosition(position); break; }
    case 1: {text1.setPosition(*new Vector2f(position.x + 140, position.y + 25)); break; }
    case 2: {text1.setPosition(*new Vector2f(position.x + 85, position.y + 25)); break; }
    case 3: {text1.setPosition(*new Vector2f(position.x + 85, position.y + 25)); break; }
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
