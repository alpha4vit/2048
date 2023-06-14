#pragma once
#include"Button.h"
#include"includes.h"
#include"move.h"
#include"Nums.h"
#include<SFML/Audio/Music.hpp>

    Text drawText(RenderWindow& window, String text, Vector2f position, int number, bool isMouseOver);
    void readResults(int& LAST_RESULT, int& BEST_RESULT);
    int readVolumeFromFile();
    Vector2i getMousePosition(RenderWindow& window, Vector2i position);
    int convertFromPositionToVolume(Vector2i position);
    Vector2f convertFromVolumeToPosition(int volume, Object sliderLine);
    void writeVolumeToFile(int volume);
    void drawBar(RenderWindow& window, vector<int> num, int state);
    void drawPlayGround(RenderWindow& window, int state);
    void drawTimer(RenderWindow& window, int& dif, int& timeLimit);
    void showCurrentResult(RenderWindow& window, int CURRENT_RESULT, int BEST_RESULT);
    void writeToFileResults(int LAST_RESULT);
    bool isMouseOver(RenderWindow& window, Text text);

enum windows {
    menuWindow, settingsWindow, gameWindow, menuOption
};

int main() {
    RenderWindow window(VideoMode(1000, 1000), L"Слияние чисел", Style::Default, ContextSettings(0, 0, 8));
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
    icon.loadFromFile("src\\logo\\logo2.png");
    window.setIcon(300, 300, icon.getPixelsPtr());
    Object bg = *new Object("src\\bg\\bg2.jpg", *new Vector2f(0, 0));
    Font font;
    font.loadFromFile("ofont.ru_Bowler.ttf");
    bool isMenu = true;
    bool isSettings = false;
    bool showOption = false;
    bool isGame = false;
    int gameState = 0;


    //menu attributes
    Object textChoose("src\\buttons\\chooseState.png", *new Vector2f(50, 20));
    Object x3("src\\buttons\\3x3.png", *new Vector2f(350, 230));
    Object x4("src\\buttons\\4x4.png", *new Vector2f(350, 430));
    Object x5("src\\buttons\\5x5.png", *new Vector2f(350, 630));
    Object time("src\\buttons\\time.png", *new Vector2f(290, 800));
    Object aboutText("src\\buttons\\about.png", *new Vector2f(380, 750));
    Object playText("src\\buttons\\playButton.png", *new Vector2f(350, 500));
    Object settingsText("src\\buttons\\settings1.png", *new Vector2f(290, 610));
    Object logo("src\\logo\\logo1.png", *new Vector2f(150, 150));

     

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
    Object sliderLine = *new Object("src\\sliders\\line.png", *new Vector2f(150, 250));
    Object slider = *new Object("src\\sliders\\slider.png", convertFromVolumeToPosition(volume, sliderLine));
    Object title = *new Object("src\\buttons\\settings.png", *new Vector2f(200, 0));

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
    bool firstMove = true;
    bool continued;
    bool fl = true;
    int timeLimit = 300;
    int startTime = 0;
    Object buttonRestart = *new Object("src\\buttons\\restart.png", *new Vector2f(870, 40));
    Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(770, 40));
    Object upArrow = *new Object("src\\buttons\\upArrow.png", *new Vector2f(450, 670));
    Object downArrow = *new Object("src\\buttons\\downArrow1.png", *new Vector2f(450, 800));
    Object leftArrow = *new Object("src\\buttons\\leftArrow1.png", *new Vector2f(320, 735));
    Object rightArrow = *new Object("src\\buttons\\rightArrow1.png", *new Vector2f(580, 735));
    Object continuePlay = *new Object("src\\buttons\\continuePlay.png", *new Vector2f(280, 380));
    Object restartWinner("src\\buttons\\playAgain1.png", *new Vector2f(200, 500));
    Object toMenuWinner("src\\buttons\\menu.png", *new Vector2f(380, 680));
    Object restart("src\\buttons\\playAgain.png", *new Vector2f(200, 500));
    Object toMenu("src\\buttons\\menu1.png", *new Vector2f(380, 680));


    while (window.isOpen()) {
        Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                writeToFileResults(CURRENT_RESULT);
                window.close();
            }
            if (ev.type == Event::MouseButtonReleased) {
                if (ev.key.code == Mouse::Left) {
                    buttonPressed = false;
                }
            }
        }

        window.clear(Color(255, 255, 255));


        window.draw(bg.sprite);


        if (isMenu) {
            Object aboutText("src\\buttons\\about.png", *new Vector2f(380, 750));
            Object playText("src\\buttons\\playButton.png", *new Vector2f(350, 500));
            Object settingsText("src\\buttons\\settings1.png", *new Vector2f(290, 610));
            Object logo("src\\logo\\logo1.png", *new Vector2f(150, 150));
            readResults(LAST_RESULT, BEST_RESULT);
            aboutText.sprite.setPosition(380.f, 750.f);
            playText.sprite.setPosition(350.f, 500.f);
            settingsText.sprite.setPosition(290.f, 610.f);
            aboutText.sprite.setScale(1.f, 1.f);
            playText.sprite.setScale(1.f, 1.f);
            settingsText.sprite.setScale(1.f, 1.f);
            

            if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed) {
                if (playText.isMouseOver(window, 0) && !showOption) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuOption;
                }
                else if (settingsText.isMouseOver(window, 0) && !showOption) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = settingsWindow;
                }
                buttonPressed = true;
            }
            if (!showOption) {
                if (playText.isMouseOver(window,  0)) {
                    Vector2f pos = playText.sprite.getPosition();
                    playText.sprite.setScale(*new Vector2f(1.02, 1.02));
                    playText.sprite.setPosition(pos.x - 2, pos.y - 2);
                }
                if (settingsText.isMouseOver(window, 0)) {
                    Vector2f pos = settingsText.sprite.getPosition();
                    settingsText.sprite.setScale(*new Vector2f(1.02, 1.02));
                    settingsText.sprite.setPosition(pos.x - 2, pos.y - 2);
                }
                if (aboutText.isMouseOver(window, 0)) {
                    Vector2f pos = aboutText.sprite.getPosition();
                    aboutText.sprite.setScale(*new Vector2f(1.02, 1.02));
                    aboutText.sprite.setPosition(pos.x - 2, pos.y - 2);
                }
            }


            window.draw(playText.sprite);
            window.draw(settingsText.sprite);
            window.draw(aboutText.sprite);
            drawText(window, to_string(LAST_RESULT), *new Vector2f(100, 100), 0, false);
            drawText(window, to_string(BEST_RESULT), *new Vector2f(200, 100), 0, false);
            window.draw(logo.sprite);

        }
        if (isSettings) {
            
            Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(870, 40));
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
            window.draw(title.sprite);
            writeVolumeToFile(volume);
        }
        if (showOption){
            RectangleShape rect;
            rect.setSize(*new Vector2f(1000, 1000));
            rect.setFillColor(*new Color(255, 255, 255, 230));
            textChoose.sprite.setPosition(50.f, 20.f);
            x3.sprite.setPosition(350.f, 230.f);
            x4.sprite.setPosition(350.f, 430.f);
            x5.sprite.setPosition(350.f, 630.f);
            time.sprite.setPosition(290.f, 800.f);
            textChoose.sprite.setScale(1.f, 1.f);
            x3.sprite.setScale(1.f, 1.f);
            x4.sprite.setScale(1.f, 1.f);
            x5.sprite.setScale(1.f, 1.f);
            time.sprite.setScale(1.f, 1.f);
            

            if (x3.isMouseOver(window, 0)) {
                Vector2f pos = x3.sprite.getPosition();
                x3.sprite.setScale(1.02, 1.02);
                x3.sprite.setPosition(pos.x - 2, pos.y - 2);
            }
            else if (x4.isMouseOver(window, 0)) {
                Vector2f pos = x4.sprite.getPosition();
                x4.sprite.setScale(1.02, 1.02);
                x4.sprite.setPosition(pos.x - 2, pos.y - 2);
            }
            else if (x5.isMouseOver(window, 0)) {
                Vector2f pos = x5.sprite.getPosition();
                x5.sprite.setScale(1.02, 1.02);
                x5.sprite.setPosition(pos.x - 2, pos.y - 2);
            }
            else if (time.isMouseOver(window, 0)) {
                Vector2f pos = time.sprite.getPosition();
                time.sprite.setScale(1.02, 1.02);
                time.sprite.setPosition(pos.x - 2, pos.y - 2);
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (x3.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 3;
                }
                else if (x4.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 4;
                }
                else if (x5.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 5;
                }
                else if (time.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 6;
                }
                else
                    showOption = false;
            }
            window.draw(rect);
            window.draw(x3.sprite);
            window.draw(x4.sprite);
            window.draw(x5.sprite);
            window.draw(textChoose.sprite);
            window.draw(time.sprite);
        }
        if (isGame) {
            buttonRestart.sprite.setPosition(*new Vector2f(870, 40));
            buttonExit.sprite.setPosition(*new Vector2f(770, 40));
            upArrow.sprite.setPosition(*new Vector2f(450, 670));
            downArrow.sprite.setPosition(*new Vector2f(450, 800));
            leftArrow.sprite.setPosition(*new Vector2f(320, 735));
            rightArrow.sprite.setPosition(*new Vector2f(580, 735));
            buttonRestart.sprite.setScale(1.f, 1.f);
            buttonExit.sprite.setScale(1.f, 1.f);
            upArrow.sprite.setScale(1.f, 1.f);
            downArrow.sprite.setScale(1.f, 1.f);
            leftArrow.sprite.setScale(1.f, 1.f);
            rightArrow.sprite.setScale(1.f, 1.f);


            
            if (!isWinner && !isGameOver) {
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
            if (!isGameOver && !isWinner && !firstMove) {
                isGameOver = checkGameOver(nums);
                isWinner = checkIsWinner(nums, state);
            }
            
            int dif = clock.getElapsedTime().asSeconds()-startTime;
            if (firstMove) {
                dif = 0;
            }
            if (state == 6  && dif >= 0) {
                drawTimer(window, dif, timeLimit);
            }
            if (state == 6 && dif < 0) {
                isGameOver = true;
            }
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
                    if (firstMove) {
                        firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::A)) {
                    keyPressed = true;
                    if (MoveLeft(nums, CURRENT_RESULT))
                        newRandNum(nums);
                    if (firstMove) {
                        firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::S)) {
                    keyPressed = true;
                    if (MoveDown(nums, CURRENT_RESULT))
                        newRandNum(nums);
                    if (firstMove) {
                        firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::W)) {
                    keyPressed = true;
                    if (MoveUp(nums, CURRENT_RESULT))
                        newRandNum(nums);
                    if (firstMove) {
                        firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                    }
                }

            }
            if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed && !isGameOver && !isWinner) {
                buttonPressed = true;
                if (buttonRestart.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; firstMove = true;
                }
                else if (buttonExit.isMouseOver(window, 0)) {
                    writeToFileResults(CURRENT_RESULT);
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow; firstMove = true;
                }
                else if (upArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveUp(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        if (firstMove) {
                            firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                        }
                    }
                }
                else if (leftArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveLeft(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        if (firstMove) {
                            firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                        }
                    }
                }
                else if (rightArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveRight(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        if (firstMove) {
                           firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                        }
                    }
                }
                else if (downArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveDown(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        if (firstMove) {
                            firstMove = false; startTime = clock.getElapsedTime().asSeconds();
                        }
                    }
                }
                
            }
            showCurrentResult(window, CURRENT_RESULT, BEST_RESULT);

            if (isGameOver || isWinner) {

                // GENERATING TEXT
               
                Object textGameOver("src\\buttons\\winner.png", *new Vector2f(150, 50));
                Object textGameOver1("src\\buttons\\over.png", *new Vector2f(150, 50));
                
                RectangleShape rect;
                rect.setSize(*new Vector2f(1000, 1000));
                rect.setFillColor(*new Color(255, 255, 255, 230));
                restart.sprite.setScale(1.f, 1.f);
                toMenu.sprite.setScale(1.f, 1.f);
                restartWinner.sprite.setScale(1.f, 1.f);
                toMenuWinner.sprite.setScale(1.f, 1.f);
                continuePlay.sprite.setScale(1.f, 1.f);
                restart.sprite.setPosition(220, 600);
                toMenu.sprite.setPosition(380 , 780);
                restartWinner.sprite.setPosition(220, 600);
                toMenuWinner.sprite.setPosition(380, 780);
                continuePlay.sprite.setPosition(280, 440);
                if (restart.isMouseOver(window, 0)) {
                    Vector2f pos = restart.sprite.getPosition();
                    restart.sprite.setScale(*new Vector2f(1.01, 1.01));
                    restart.sprite.setPosition(*new Vector2f(pos.x-2, pos.y-2));
                }
                if (toMenu.isMouseOver(window, 0)) {
                    Vector2f pos = toMenu.sprite.getPosition();
                    toMenu.sprite.setScale(*new Vector2f(1.01, 1.01));
                    toMenu.sprite.setPosition(*new Vector2f(pos.x - 2, pos.y - 2));
                }
                if (restartWinner.isMouseOver(window, 0)) {
                    Vector2f pos = restartWinner.sprite.getPosition();
                    restartWinner.sprite.setScale(*new Vector2f(1.01, 1.01));
                    restartWinner.sprite.setPosition(*new Vector2f(pos.x - 2, pos.y - 2));
                }
                if (toMenuWinner.isMouseOver(window, 0)) {
                    Vector2f pos = toMenuWinner.sprite.getPosition();
                    toMenuWinner.sprite.setScale(*new Vector2f(1.01, 1.01));
                    toMenuWinner.sprite.setPosition(*new Vector2f(pos.x - 2, pos.y - 2));
                }
                if (continuePlay.isMouseOver(window, 0)) {
                    Vector2f pos = continuePlay.sprite.getPosition();
                    continuePlay.sprite.setScale(*new Vector2f(1.01, 1.01));
                    continuePlay.sprite.setPosition(*new Vector2f(pos.x - 2, pos.y - 2));
                }
                
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (restart.isMouseOver(window, 0)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; fstart = true;
                    }
                    else if (toMenu.isMouseOver(window, 0)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow;
                    }
                    else if (toMenuWinner.isMouseOver(window, 0)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow;
                    }
                    else if (restartWinner.isMouseOver(window, 0)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; fstart = true;
                    }
                    else if (continuePlay.isMouseOver(window, 0)) {
                        isWinner = false; isGameOver = false;
                    }

                }


                window.draw(rect);
                
                if (isWinner) {
                    Object medal("src\\buttons\\medal.png", *new Vector2f(860, 350));
                    medal.sprite.setRotation(20);
                    window.draw(medal.sprite);
                    window.draw(toMenuWinner.sprite);
                    window.draw(restartWinner.sprite);
                    window.draw(continuePlay.sprite);
                }
                else {
                    window.draw(textGameOver1.sprite);
                    window.draw(toMenu.sprite);
                    window.draw(restart.sprite);
                }
            }
        }
        if (transition) {
            float duration = 0.6;
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
                    case menuOption: { showOption = true; break; }
                    case settingsWindow: { isSettings = true; break; }
                    case menuWindow: {
                        isMenu = true; break; }
                    case gameWindow: { 
                        isGame = true;
                        if (fstart) {
                            nums = genNums(state);
                            genFnum(nums);
                            fstart = false;
                            firstMove = true;
                            isWinner = false;
                            isGameOver = false;
                            writeToFileResults(CURRENT_RESULT);
                            CURRENT_RESULT = 0;
                            //nums[2][2][0] = 4096;
                        }
                        break; }
                    default:
                        break;
                    }
                    alpha = 255 - ((transitionTime - (duration / 2)) / (duration / 2)) * 255;
                }
                else {
                    fstart = true;
                    transition = false;
                }
            }
            window.draw(transitionRect);
        }

        window.display();
    }
}


void drawBar(RenderWindow& window, vector<int> num, int state) {
    int temp = state;
    if (state == 6)
        temp = 4;
    Image img = Image();
    img.loadFromFile("src\\" + to_string(temp) + "\\" + to_string(num[0]) + ".png");
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
    current_number.setPosition(*new Vector2f(800, 220));

    Text text("YOUR SCORE:", font, 25);
    text.setFillColor(Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(*new Vector2f(745, 185));

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



Text drawText(RenderWindow& window, String text, Vector2f position, int number, bool isOption) {
    Font font;
    font.loadFromFile("font1.ttf");
    Text text1(text, font, 40);
    text1.setFillColor(Color(255, 255, 255));
    if (isMouseOver(window, text1)) {
        text1.setFillColor(Color(176, 176, 176));
    }
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


void drawTimer(RenderWindow& window, int& dif, int& timeLimit) {
  

    Font font;
    font.loadFromFile("ofont.ru_Bowler.ttf");
    Text text(to_string(timeLimit-dif) + " seconds", font, 40);
    text.setPosition(670, 135);
    float progress = dif / (float)timeLimit;
    Color startColor(0, 255, 0); 
    Color middleColor(255, 255, 0); 
    Color endColor(255, 0, 0); 

    sf::Color currentColor;
    if (progress < 0.5f)
    {
        float subProgress = progress / 0.5f;
        currentColor.r = static_cast<sf::Uint8>((1 - subProgress) * startColor.r + subProgress * middleColor.r);
        currentColor.g = static_cast<sf::Uint8>((1 - subProgress) * startColor.g + subProgress * middleColor.g);
        currentColor.b = static_cast<sf::Uint8>((1 - subProgress) * startColor.b + subProgress * middleColor.b);
    }
    else
    {
        float subProgress = (progress - 0.5f) / 0.5f;
        currentColor.r = static_cast<sf::Uint8>((1 - subProgress) * middleColor.r + subProgress * endColor.r);
        currentColor.g = static_cast<sf::Uint8>((1 - subProgress) * middleColor.g + subProgress * endColor.g);
        currentColor.b = static_cast<sf::Uint8>((1 - subProgress) * middleColor.b + subProgress * endColor.b);
    }
    text.setFillColor(currentColor);
    window.draw(text);
}
