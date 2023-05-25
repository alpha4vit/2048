#pragma once

#include"Button.h"
#include"includes.h"
#include"move.h"
#include"Nums.h"
#include<SFML/Audio/Music.hpp>
#include"KeyChecker.h"

void MainMenu(RenderWindow& window, Music& music);
void settings(RenderWindow& window, Music& music);
int play(RenderWindow& window, Music& music, int state);
Text drawText(RenderWindow& window, String text, Vector2f position, int number, bool isMouseOver);
void readResults(int& LAST_RESULT, int& BEST_RESULT);
int readVolumeFromFile();
Vector2i getMousePosition(RenderWindow& window, Vector2i position);
int convertFromPositionToVolume(Vector2i position);
Vector2f convertFromVolumeToPosition(int volume, Object sliderLine);
void writeVolumeToFile(int volume);
void drawBar(RenderWindow& window, vector<int> num, int state);
void drawPlayGround(RenderWindow& window, int state);
void drawButton(RenderWindow& window, Button& button, bool isOption);
void showCurrentResult(RenderWindow& window, int CURRENT_RESULT, int BEST_RESULT);
void writeToFileResults(int LAST_RESULT);
void openNewWindow(RenderWindow& window, int win, Music& music, int state);
bool isMouseOver(RenderWindow& window, Text text);

enum windows {
    menuWindow, settingsWindow, gameWindow
};

int main() {
    RenderWindow window(VideoMode(1000, 1000), "2048", Style::Default, ContextSettings(0, 0, 8));
    Music music;
    music.openFromFile("src\\sounds\\backsound.ogg");
    music.play();
    music.setLoop(true);
    int volume = readVolumeFromFile();
    music.setVolume(volume);
    MainMenu(window, music);
}


void MainMenu(RenderWindow& menu, Music& music) {

    clock_t start_time = 0;
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
    Font font;
    font.loadFromFile("font1.ttf");
    Text title(L"CÀ»ﬂÕ»≈ ◊»—≈À", font, 62);
    title.setFillColor(Color::Black);
    title.setPosition(*new Vector2f(100, 100));

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
                settings(menu, music);
            }
            else {
                showOption = false;
            }
        }


        drawButton(menu, buttonPlay, showOption);
        drawButton(menu, buttonSettings, showOption);
        drawButton(menu, buttonAboutUs, showOption);
        drawText(menu, L"»√–¿“‹", buttonPlay.getSprite().getPosition(), 1, buttonPlay.isMouseOver(menu) && !showOption);
        drawText(menu, L"Õ¿—“–Œ… »", buttonSettings.getSprite().getPosition(), 2, buttonSettings.isMouseOver(menu) && !showOption);
        drawText(menu, L"Œ Õ¿—", buttonAboutUs.getSprite().getPosition(), 3, buttonAboutUs.isMouseOver(menu) && !showOption);
        drawText(menu, to_string(LAST_RESULT), *new Vector2f(100, 100), 0, false);
        drawText(menu, to_string(BEST_RESULT), *new Vector2f(200, 100), 0, false);


        if (showOption) {
            RectangleShape rect;
            rect.setSize(*new Vector2f(1000, 1000));
            rect.setFillColor(*new Color(255, 255, 255, 200)); 
            Font font;
            font.loadFromFile("ofont.ru_Bowler.ttf");
            Text gameMode(L"CHOOSE GAME MODE ’”…", font, 62);
            gameMode.setFillColor(Color::Green);
            gameMode.setPosition(*new Vector2f(130, 100));
            Text x3("3x3", font, 90);
            x3.setPosition(*new Vector2f(100, 400));
            x3.setFillColor(Color::Green);
            Text x4("4x4", font, 90);
            x4.setPosition(*new Vector2f(400, 400));
            x4.setFillColor(Color::Green);
            Text x5("5x5", font, 90);
            x5.setPosition(*new Vector2f(700, 400));
            x5.setFillColor(Color::Green);

            if (isMouseOver(menu, x3)) {
                x3.setFillColor(Color(117, 117, 117));
                x3.setScale(*new Vector2f(1.05, 1.05));
                x3.setPosition(95, 395);
            }
            if (isMouseOver(menu, x4)) {
                x4.setFillColor(Color(117, 117, 117));
                x4.setScale(*new Vector2f(1.05, 1.05));
                x4.setPosition(395, 395);
            }
            if (isMouseOver(menu, x5)) {
                x5.setFillColor(Color(117, 117, 117));
                x5.setScale(*new Vector2f(1.05, 1.05));
                x5.setPosition(695, 395);
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isMouseOver(menu, x3))
                    play(menu, music, 3);
                else if (isMouseOver(menu, x4))
                    play(menu, music, 4);
                else if (isMouseOver(menu, x5))
                    play(menu, music, 5);
            }
            menu.draw(rect);
            menu.draw(x3);
            menu.draw(x4);
            menu.draw(x5);
            menu.draw(gameMode);
        }
        menu.draw(title);
        menu.display();
    }
}

void settings(RenderWindow& settings, Music& music) {
   
    
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
            if (sliderLine.isMouseOver(settings, 0)) {
                slider.sprite.setPosition(mouseCoord.x, sliderLine.sprite.getPosition().y-18);
                volume = convertFromPositionToVolume(mouseCoord);
                music.setVolume(volume);
            }
            else if (buttonExit.isMouseOver(settings, 3)) {
                MainMenu(settings, music);
            }
        }
        settings.draw(slider.sprite);
        settings.display();
    }
    writeVolumeToFile(volume);
}


int play(RenderWindow& game, Music& music, int state)
{

    
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
    int temp;
    int BEST_RESULT;
    readResults(temp, BEST_RESULT);
    bool isGameOver = false;
    bool isWinner = false;
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

        isGameOver = checkGameOver(nums);
        isWinner = checkIsWinner(nums, state);
        if (ev.type == Event::MouseButtonReleased && ev.mouseButton.button == Mouse::Left) {
            buttonPressed = false;
        }
        if (ev.type == Event::KeyReleased && (ev.key.code == Keyboard::W || ev.key.code == Keyboard::S || ev.key.code == Keyboard::D || ev.key.code == Keyboard::A)) {
            keyPressed = false;
        }


        if (!keyPressed && !isGameOver) {
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                keyPressed = true;
                if (MoveRight(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
            else if (Keyboard::isKeyPressed(Keyboard::A)) {
                keyPressed = true;
                if (MoveLeft(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
            else if (Keyboard::isKeyPressed(Keyboard::S)) {
                keyPressed = true;
                if (MoveDown(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
            else if (Keyboard::isKeyPressed(Keyboard::W)) {
                keyPressed = true;
                if (MoveUp(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }

        }

        if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed && !isGameOver) {
            buttonPressed = true;
            if (buttonRestart.isMouseOver(game, 3)) {
                play(game, music, state);
            }
            else if (buttonExit.isMouseOver(game, 3)) {
                writeToFileResults(CURRENT_RESULT);
                MainMenu(game, music);
            }
            else if (upArrow.isMouseOver(game, 2)) {
                if (MoveUp(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
            else if (leftArrow.isMouseOver(game, 2)) {
                if (MoveLeft(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
            else if (rightArrow.isMouseOver(game, 2)) {
                if (MoveRight(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
            else if (downArrow.isMouseOver(game, 2)) {
                if (MoveDown(nums, CURRENT_RESULT))
                    newRandNum(nums);
            }
        }
        showCurrentResult(game, CURRENT_RESULT, BEST_RESULT);
    

        if (isGameOver || isWinner) {
            
            // GENERATING TEXT

            Font font;
            font.loadFromFile("ofont.ru_Bowler.ttf");
            RectangleShape rect;
            rect.setSize(*new Vector2f(1000, 1000));
            rect.setFillColor(*new Color(255, 255, 255, 230));
            Text textAgain("PLAY  AGAIN", font, 64);
            textAgain.setPosition(*new Vector2f(100, 500));
            Text textExit("EXIT", font, 64);
            textExit.setPosition(*new Vector2f(680, 500));
            Text textGameOver;
            textGameOver.setFont(font);
            textGameOver.setCharacterSize(105);
            textGameOver.setPosition(*new Vector2f(150, 60));
            if (isGameOver) {
                textGameOver.setString("GAME OVER");
            }
            else {
                textGameOver.setString("YOU'RE WINNER");
            }
            if (!isMouseOver(game, textAgain)) {
                textAgain.setFillColor(Color(117, 117, 117));
                textAgain.setPosition(*new Vector2f(100, 500));
            }
            else {
                textAgain.setScale(*new Vector2f(1.05, 1.05));
                textAgain.setPosition(*new Vector2f(95, 495));
                textAgain.setFillColor(Color::Red);
            }
            if (!isMouseOver(game, textExit)) {
                textExit.setFillColor(Color(117, 117, 117));
            }
            else {
                textExit.setScale(*new Vector2f(1.05, 1.05));
                textExit.setPosition(*new Vector2f(675, 495));
                textExit.setFillColor(Color::Red);
            }
            if (!isMouseOver(game, textGameOver)) {
                textGameOver.setFillColor(Color::Red);
            }
            else {
                textGameOver.setScale(*new Vector2f(1.05, 1.05));
                textGameOver.setPosition(*new Vector2f(145, 55));
                textGameOver.setFillColor(Color::Blue);
            }


            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isMouseOver(game, textAgain)) {
                    writeToFileResults(CURRENT_RESULT);
                    play(game, music, state);
                }
                else if (isMouseOver(game, textExit)) {
                    writeToFileResults(CURRENT_RESULT);
                    MainMenu(game, music);
                }
            }
           

            game.draw(rect);
            game.draw(textAgain);
            game.draw(textExit);
            game.draw(textGameOver);
        }


        game.display();
    }

    return CURRENT_RESULT;
}


void openNewWindow(RenderWindow& window, int win, Music& music, int state) {
    int transparency = 255;
    RectangleShape rect;
    rect.setPosition(*new Vector2f(0, 0));
    rect.setSize(*new Vector2f(1000, 1000));
    rect.setFillColor(Color(255, 255, 255, transparency));

    clock_t start_time = clock();
    while (window.isOpen()) {
        Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
            }
        }

        
        window.clear(Color(255, 255, 255));
        window.draw(rect);
        clock_t current_time = clock();

        if (double(current_time - start_time) / CLOCKS_PER_SEC * 1000.0 > 1000) {
            return;
        }


        if (double(current_time - start_time) / CLOCKS_PER_SEC * 1000.0 < 1000) {
            --transparency;
            rect.setFillColor(Color(255, 255, 255, transparency));
        }
        else {
            ++transparency;
            rect.setFillColor(Color(255, 255, 255, transparency));
        }
        window.display();
    }
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

void showCurrentResult(RenderWindow& window, int CURRENT_RESULT, int BEST_RESULT) {
    Font font;
    font.loadFromFile("ofont.ru_Bowler.ttf");


    Text current_number(to_string(CURRENT_RESULT), font, 40);
    current_number.setFillColor(Color::Black);
    current_number.setStyle(sf::Text::Bold);
    current_number.setPosition(*new Vector2f(850, 220));

    Text text("YOUR SCORE:", font, 25);
    text.setFillColor(Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(*new Vector2f(770, 185));

    Text text1("HIGHEST SCORE:", font, 25);
    text1.setFillColor(Color::Black);
    text1.setStyle(sf::Text::Bold);
    text1.setPosition(*new Vector2f(725, 275));

    Text highest_number(to_string(BEST_RESULT), font, 40);
    highest_number.setFillColor(Color::Black);
    highest_number.setStyle(sf::Text::Bold);
    highest_number.setPosition(*new Vector2f(800, 310));

    window.draw(current_number);
    window.draw(highest_number);
    window.draw(text);
    window.draw(text1);
}

void drawButton(RenderWindow& window, Button& button, bool isOption) {
    if (button.isMouseOver(window) && !isOption) {
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



Text drawText(RenderWindow& window, String text, Vector2f position, int number, bool isMouseOver) {
    Font font;
    font.loadFromFile("font1.ttf");
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
    return text1;
}


void readResults(int& LAST_RESULT, int& BEST_RESULT) {
    fstream file;
    file.open("result.txt");
    file >> LAST_RESULT;
    file >> BEST_RESULT;
    file.close();   
}


bool isMouseOver(RenderWindow& window, Text text)
{
    int sizeX = 165;
    int sizeY = 67;
    if (text.getString() == "PLAY  AGAIN") {
        sizeX = 450;
    }
    else if (text.getString() == "GAME OVER") {
        sizeX = 710;
        sizeY = 103;
    }
    else if (text.getString() == "3x3" || text.getString() == "4x4" || text.getString() == "5x5") {
        sizeX = 210;
        sizeY = 90;
    }
    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > text.getPosition().x && mousePos.x <text.getPosition().x + sizeX
        && mousePos.y > text.getPosition().y && mousePos.y < text.getPosition().y + sizeY)
        return true;
    else
        return false;
}


/*if (start_time == 0) {
                       start_time = clock();
                   }
                   clock_t current_time = clock();
                   int transparency = 255;
                   RectangleShape rect;
                   rect.setPosition(*new Vector2f(0, 0));
                   rect.setSize(*new Vector2f(1000, 1000));
                   rect.setFillColor(Color(255, 255, 255, transparency));
                   if (double(current_time - start_time) / CLOCKS_PER_SEC * 1000.0 < 1000) {
                       --transparency;
                       rect.setFillColor(Color(255, 255, 255, transparency));
                   }
                   else {
                       play(menu, music, 3);
                       ++transparency;
                       rect.setFillColor(Color(255, 255, 255, transparency));
                   }
                   if (double(current_time - start_time) / CLOCKS_PER_SEC * 1000.0 > 1000){
                       start_time = 0;
                   }*/

