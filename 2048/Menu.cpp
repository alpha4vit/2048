#pragma once

#include"Button.h"
#include"includes.h"
#include"move.h"
#include"Nums.h"
#include<SFML/Audio/Music.hpp>
#include"KeyChecker.h"

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
bool isMouseOver(RenderWindow& window, Text text);

enum windows {
    menuWindow, settingsWindow, gameWindow, menuOption
};

int main() {
    RenderWindow window(VideoMode(1000, 1000), "2048", Style::Default, ContextSettings(0, 0, 8));
    Music music;
    music.openFromFile("src\\sounds\\backsound.ogg");
    music.play();
    music.setLoop(true);
    int volume = readVolumeFromFile();
    music.setVolume(volume);
    int LAST_RESULT;
    int BEST_RESULT;
    readResults(LAST_RESULT, BEST_RESULT);


    //SETTING ICON
    Image icon = *new Image();
    icon.loadFromFile("src\\logo\\logo.png");
    window.setIcon(427, 427, icon.getPixelsPtr());
    Object bg = *new Object("src\\bg\\bg2.jpg", *new Vector2f(0, 0));
    Font font;
    bool isMenu = true;
    bool isSettings = false;
    bool showOption = false;
    bool isGame = false;
    int gameState = 0;


    //menu attributes
    Button buttonPlay = *new Button(*new Vector2f(300, 500));
    Button buttonSettings = *new Button(*new Vector2f(300, 665));
    Button buttonAboutUs = *new Button(*new Vector2f(300, 820));



    //transition attributes
    RectangleShape transitionRect;
    transitionRect.setPosition(0, 0);
    transitionRect.setSize(*new Vector2f(1000, 1000));
    transitionRect.setFillColor(Color::Black);
    int alpha = 0;
    Clock clock;
    float transitionStart = 0;
    bool transition = false;
    int windowType;


    //settings attributes
    Object sliderLine = *new Object("src\\sliders\\line.png", *new Vector2f(150, 200));
    Object slider = *new Object("src\\sliders\\slider.png", convertFromVolumeToPosition(volume, sliderLine));

    //game attributes
    int state;
    bool buttonPressed = false;
    bool keyPressed = false;
    double tempTime;
    int CURRENT_RESULT = 0;
    int temp;
    readResults(temp, BEST_RESULT);
    bool isGameOver = false;
    bool isWinner = false;
    bool fstart = true;
    vector<vector<vector<int>>> nums;

    while (window.isOpen()) {
        Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color(255, 255, 255));


        window.draw(bg.sprite);


        if (isMenu) {
            
            Text title(L"CÀ»ﬂÕ»≈ ◊»—≈À", font, 62);
            title.setFillColor(Color::Black);
            title.setPosition(*new Vector2f(100, 100));


            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (buttonPlay.isMouseOver(window)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuOption;
                }
                else if (buttonSettings.isMouseOver(window)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = settingsWindow;
                }
                else if (!transition) {
                    showOption = false;
                }
            }

            drawButton(window, buttonPlay, showOption);
            drawButton(window, buttonSettings, showOption);
            drawButton(window, buttonAboutUs, showOption);
            drawText(window, L"»√–¿“‹", buttonPlay.getSprite().getPosition(), 1, buttonPlay.isMouseOver(window) && !showOption);
            drawText(window, L"Õ¿—“–Œ… »", buttonSettings.getSprite().getPosition(), 2, buttonSettings.isMouseOver(window) && !showOption);
            drawText(window, L"Œ Õ¿—", buttonAboutUs.getSprite().getPosition(), 3, buttonAboutUs.isMouseOver(window) && !showOption);
            drawText(window, to_string(LAST_RESULT), *new Vector2f(100, 100), 0, false);
            drawText(window, to_string(BEST_RESULT), *new Vector2f(200, 100), 0, false);
            window.draw(title);

            if (showOption) {
                RectangleShape rect;
                rect.setSize(*new Vector2f(1000, 1000));
                rect.setFillColor(*new Color(255, 255, 255, 200));
                Font font;
                font.loadFromFile("ofont.ru_Bowler.ttf");
                Text gameMode(L"¬€¡≈–»“≈ –≈∆»Ã", font, 62);
                gameMode.setFillColor(Color::Green);
                gameMode.setPosition(*new Vector2f(180, 150));
                Text x3("3x3", font, 90);
                x3.setPosition(*new Vector2f(100, 400));
                x3.setFillColor(Color::Green);
                Text x4("4x4", font, 90);
                x4.setPosition(*new Vector2f(400, 400));
                x4.setFillColor(Color::Green);
                Text x5("5x5", font, 90);
                x5.setPosition(*new Vector2f(700, 400));
                x5.setFillColor(Color::Green);

                if (isMouseOver(window, x3)) {
                    x3.setFillColor(Color(117, 117, 117));
                    x3.setScale(*new Vector2f(1.05, 1.05));
                    x3.setPosition(95, 395);
                }
                if (isMouseOver(window, x4)) {
                    x4.setFillColor(Color(117, 117, 117));
                    x4.setScale(*new Vector2f(1.05, 1.05));
                    x4.setPosition(395, 395);
                }
                if (isMouseOver(window, x5)) {
                    x5.setFillColor(Color(117, 117, 117));
                    x5.setScale(*new Vector2f(1.05, 1.05));
                    x5.setPosition(695, 395);
                }

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (isMouseOver(window, x3)) {
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; gameState = 3;
                    }
                    else if (isMouseOver(window, x4)) {
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; gameState = 4;
                    }
                    else if (isMouseOver(window, x5)) {
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; gameState = 5;
                    }
                }
                window.draw(rect);
                window.draw(x3);
                window.draw(x4);
                window.draw(x5);
                window.draw(gameMode);
            }
        }
        if (isSettings) {
            Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(770, 40));
            drawText(window, "SETTINGS", *new Vector2f(400, 50), 0, false);
            window.draw(sliderLine.sprite);
            if (buttonExit.isMouseOver(window, 0)) {
                buttonExit.sprite.setScale(1.05f, 1.05f);
                buttonExit.sprite.setPosition(buttonExit.sprite.getPosition().x - 2.f, buttonExit.sprite.getPosition().y - 2.f);
            }
            window.draw(buttonExit.sprite);
            if (Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mouseCoord = getMousePosition(window, Mouse::getPosition());
                if (sliderLine.isMouseOver(window, 1)) {
                    slider.sprite.setPosition(mouseCoord.x-50, sliderLine.sprite.getPosition().y - 18);
                    volume = convertFromPositionToVolume(mouseCoord);
                    music.setVolume(volume);
                }
                else if (buttonExit.isMouseOver(window, 0)) {
                    if (!transition) {
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow;
                    }
                }
            }
            window.draw(buttonExit.sprite);
            window.draw(slider.sprite);
            writeVolumeToFile(volume);
        }
        if (showOption){
            RectangleShape rect;
            rect.setSize(*new Vector2f(1000, 1000));
            rect.setFillColor(*new Color(255, 255, 255, 200));
            Font font;
            font.loadFromFile("ofont.ru_Bowler.ttf");
            Text gameMode(L"¬€¡≈–»“≈ –≈∆»Ã", font, 62);
            gameMode.setFillColor(Color::Green);
            gameMode.setPosition(*new Vector2f(180, 150));
            Text x3("3x3", font, 90);
            x3.setPosition(*new Vector2f(100, 400));
            x3.setFillColor(Color::Green);
            Text x4("4x4", font, 90);
            x4.setPosition(*new Vector2f(400, 400));
            x4.setFillColor(Color::Green);
            Text x5("5x5", font, 90);
            x5.setPosition(*new Vector2f(700, 400));
            x5.setFillColor(Color::Green);

            if (isMouseOver(window, x3)) {
                x3.setFillColor(Color(117, 117, 117));
                x3.setScale(*new Vector2f(1.05, 1.05));
                x3.setPosition(95, 395);
            }
            if (isMouseOver(window, x4)) {
                x4.setFillColor(Color(117, 117, 117));
                x4.setScale(*new Vector2f(1.05, 1.05));
                x4.setPosition(395, 395);
            }
            if (isMouseOver(window, x5)) {
                x5.setFillColor(Color(117, 117, 117));
                x5.setScale(*new Vector2f(1.05, 1.05));
                x5.setPosition(695, 395);
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (isMouseOver(window, x3)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 3;
                }
                else if (isMouseOver(window, x4)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 4;
                }
                else if (isMouseOver(window, x5)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 5;
                }
            }
            window.draw(rect);
            window.draw(x3);
            window.draw(x4);
            window.draw(x5);
            window.draw(gameMode);
        }
        if (isGame) {
            Object buttonRestart = *new Object("src\\buttons\\restart.png", *new Vector2f(870, 40));
            Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(770, 40));
            Object upArrow = *new Object("src\\buttons\\upArrow.png", *new Vector2f(450, 670));
            Object downArrow = *new Object("src\\buttons\\downArrow1.png", *new Vector2f(450, 800));
            Object leftArrow = *new Object("src\\buttons\\leftArrow1.png", *new Vector2f(320, 735));
            Object rightArrow = *new Object("src\\buttons\\rightArrow1.png", *new Vector2f(580, 735));
            

            if (buttonExit.isMouseOver(window, 0)) {
                buttonExit.sprite.setScale(1.05f, 1.05f);
                buttonExit.sprite.setPosition(buttonExit.sprite.getPosition().x - 2.f, buttonExit.sprite.getPosition().y - 2.f);
            }
            else if (buttonRestart.isMouseOver(window, 0)) {
                buttonRestart.sprite.setScale(1.05f, 1.05f);
                buttonRestart.sprite.setPosition(buttonRestart.sprite.getPosition().x - 2.f, buttonRestart.sprite.getPosition().y - 2.f);
            }
            else if (downArrow.isMouseOver(window, 0)) {
                downArrow.sprite.setScale(1.05f, 1.05f);
                downArrow.sprite.setPosition(downArrow.sprite.getPosition().x - 2.f, downArrow.sprite.getPosition().y - 2.f);
            }
            else if (upArrow.isMouseOver(window, 0)) {
                upArrow.sprite.setScale(1.05f, 1.05f);
                upArrow.sprite.setPosition(upArrow.sprite.getPosition().x - 2.f, upArrow.sprite.getPosition().y - 2.f);
            }
            else if (leftArrow.isMouseOver(window, 0)) {
                leftArrow.sprite.setScale(1.05f, 1.05f);
                leftArrow.sprite.setPosition(leftArrow.sprite.getPosition().x - 2.f, leftArrow.sprite.getPosition().y - 2.f);
            }
            else if (rightArrow.isMouseOver(window, 0)) {
                rightArrow.sprite.setScale(1.05f, 1.05f);
                rightArrow.sprite.setPosition(rightArrow.sprite.getPosition().x - 2.f, rightArrow.sprite.getPosition().y - 2.f);
            }

            window.draw(bg.sprite);
            window.draw(buttonRestart.sprite);
            window.draw(buttonExit.sprite);
            window.draw(downArrow.sprite);
            window.draw(upArrow.sprite);
            window.draw(leftArrow.sprite);
            window.draw(rightArrow.sprite);
            drawPlayGround(window, state);


            for (int i = 0; i < size(nums); ++i) {
                for (int j = 0; j < size(nums[i]); ++j) {
                    if (nums[i][j][0] != 0) {
                        drawBar(window, nums[i][j], state);
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
                if (buttonRestart.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; fstart = true;
                }
                else if (buttonExit.isMouseOver(window, 0)) {
                    writeToFileResults(CURRENT_RESULT);
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow; fstart = true;
                }
                else if (upArrow.isMouseOver(window, 0)) {
                    if (MoveUp(nums, CURRENT_RESULT))
                        newRandNum(nums);
                }
                else if (leftArrow.isMouseOver(window, 0)) {
                    if (MoveLeft(nums, CURRENT_RESULT))
                        newRandNum(nums);
                }
                else if (rightArrow.isMouseOver(window, 0)) {
                    if (MoveRight(nums, CURRENT_RESULT))
                        newRandNum(nums);
                }
                else if (downArrow.isMouseOver(window, 0)) {
                    if (MoveDown(nums, CURRENT_RESULT))
                        newRandNum(nums);
                }
            }
            showCurrentResult(window, CURRENT_RESULT, BEST_RESULT);


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
                if (!isMouseOver(window, textAgain)) {
                    textAgain.setFillColor(Color(117, 117, 117));
                    textAgain.setPosition(*new Vector2f(100, 500));
                }
                else {
                    textAgain.setScale(*new Vector2f(1.05, 1.05));
                    textAgain.setPosition(*new Vector2f(95, 495));
                    textAgain.setFillColor(Color::Red);
                }
                if (!isMouseOver(window, textExit)) {
                    textExit.setFillColor(Color(117, 117, 117));
                }
                else {
                    textExit.setScale(*new Vector2f(1.05, 1.05));
                    textExit.setPosition(*new Vector2f(675, 495));
                    textExit.setFillColor(Color::Red);
                }
                if (!isMouseOver(window, textGameOver)) {
                    textGameOver.setFillColor(Color::Red);
                }
                else {
                    textGameOver.setScale(*new Vector2f(1.05, 1.05));
                    textGameOver.setPosition(*new Vector2f(145, 55));
                    textGameOver.setFillColor(Color::Blue);
                }


                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (isMouseOver(window, textAgain)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; fstart = true;
                    }
                    else if (isMouseOver(window, textExit)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow; fstart = true;
                    }
                }


                window.draw(rect);
                window.draw(textAgain);
                window.draw(textExit);
                window.draw(textGameOver);
            }
        }
        if (transition) {
            int duration = 2;
            if (!transition) {
                transition = true;
                transitionStart = clock.getElapsedTime().asSeconds();
            }
            else {
                float transitionTime = clock.getElapsedTime().asSeconds() - transitionStart;
                transitionRect.setFillColor(sf::Color(0, 0, 0, alpha));
                
                if (clock.getElapsedTime().asSeconds() < transitionStart + duration / 2) {
                    alpha = (transitionTime / (duration / 2)) * 255;
                }
                else if (clock.getElapsedTime().asSeconds() < transitionStart + duration) {
                    if (isMenu && windowType != menuWindow && windowType != menuOption) isMenu = false;
                    if (isGame && windowType != gameWindow) isGame = false;
                    if (showOption && windowType != menuOption) showOption = false;
                    if (isSettings && windowType != settingsWindow) isSettings = false;

                    switch (windowType)
                    {
                    case menuOption: { showOption = true;  break; }
                    case settingsWindow: { isSettings = true;break; }
                    case menuWindow: { isMenu = true; break; }
                    case gameWindow: { 
                        if (fstart)
                        nums = genNums(state); 
                        genFnum(nums); 
                        isGame = true; break; }
                    default:
                        break;
                    }
                    alpha = 255 - ((transitionTime - (duration / 2)) / (duration / 2)) * 255;
                }
                else {
                    transition = false;
                }
            }
            window.draw(transitionRect);
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
    return *new Vector2f(volume * 5.8 + 150, sliderLine.sprite.getPosition().y - 18);
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
    case 1: {text1.setPosition(*new Vector2f(position.x + 115, position.y + 25)); break; }
    case 2: {text1.setPosition(*new Vector2f(position.x + 55, position.y + 25)); break; }
    case 3: {text1.setPosition(*new Vector2f(position.x + 130, position.y + 25)); break; }
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
    int sizeX = text.getLocalBounds().width+5;
    int sizeY = text.getLocalBounds().height+27;

    Vector2i mousePos = Mouse::getPosition(window);
    if (mousePos.x > text.getPosition().x && mousePos.x <text.getPosition().x + sizeX
        && mousePos.y > text.getPosition().y && mousePos.y < text.getPosition().y + sizeY)
        return true;
    else
        return false;
}

