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

    void showCurrentResult(RenderWindow& window, int CURRENT_RESULT, int BEST_RESULT);
    void writeToFileResults(int LAST_RESULT);
    bool isMouseOver(RenderWindow& window, Text text);

enum windows {
    menuWindow, settingsWindow, gameWindow, menuOption
};

int main() {
    RenderWindow window(VideoMode(1000, 1000), L"—ÎËˇÌËÂ ˜ËÒÂÎ", Style::Default, ContextSettings(0, 0, 8));
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
    Object settingsButton = *new Object("src\\buttons\\settingsButton.png", *new Vector2f(300, 655));
    Object playButton = *new Object("src\\buttons\\playButton.png", *new Vector2f(350, 500));




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
    bool firstMove = false;

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
            readResults(LAST_RESULT, BEST_RESULT);
            Text playText(L"»√–¿“‹", font, 72);
            playText.setFillColor(Color::White);
            playText.setPosition(340, 500);
            Text settingsText(L"Õ¿—“–Œ… »", font, 72);
            settingsText.setFillColor(Color::White);
            settingsText.setPosition(250, 665);
            Text aboutText(L"Œ Õ¿—", font, 72);
            aboutText.setFillColor(Color::White);
            aboutText.setPosition(350, 820);
            Object logo("src\\logo\\logo1.png", *new Vector2f(150, 150));

            if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed) {
                if (isMouseOver(window, playText) && !showOption) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuOption;
                }
                else if (isMouseOver(window, settingsText) && !showOption) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = settingsWindow;
                }
                else if (!transition) {
                    showOption = false;
                }
                buttonPressed = true;
            }
            if (!showOption) {
                if (isMouseOver(window, playText)) {
                    Vector2f pos = playText.getPosition();
                    playText.setFillColor(Color(117, 117, 117));
                    playText.setScale(*new Vector2f(1.05, 1.05));
                    playText.setPosition(pos.x - 5, pos.y - 5);
                }
                if (isMouseOver(window, settingsText)) {
                    Vector2f pos = settingsText.getPosition();
                    settingsText.setFillColor(Color(117, 117, 117));
                    settingsText.setScale(*new Vector2f(1.05, 1.05));
                    settingsText.setPosition(pos.x - 5, pos.y - 5);
                }
                if (isMouseOver(window, aboutText)) {
                    Vector2f pos = aboutText.getPosition();
                    aboutText.setFillColor(Color(117, 117, 117));
                    aboutText.setScale(*new Vector2f(1.05, 1.05));
                    aboutText.setPosition(pos.x - 5, pos.y - 5);
                }
            }


            window.draw(playButton.sprite);
            window.draw(settingsButton.sprite);
            window.draw(aboutText);
            drawText(window, to_string(LAST_RESULT), *new Vector2f(100, 100), 0, false);
            drawText(window, to_string(BEST_RESULT), *new Vector2f(200, 100), 0, false);
            window.draw(logo.sprite);

        }
        if (isSettings) {
            //Object audioLogo = *new Object("src\\buttons\\audio.png", *new Vector2f(60, 230));
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
           // window.draw(audioLogo.sprite);
            writeVolumeToFile(volume);
        }
        if (showOption){
            RectangleShape rect;
            rect.setSize(*new Vector2f(1000, 1000));
            rect.setFillColor(*new Color(255, 255, 255, 230));
            Object textChoose("src\\buttons\\chooseState.png", *new Vector2f(50, 40));
            Object x3("src\\buttons\\3x3.png", *new Vector2f(350, 300));
            Object x4("src\\buttons\\4x4.png", *new Vector2f(350, 520));
            Object x5("src\\buttons\\5x5.png", *new Vector2f(350, 740));
            Object set = *new Object("src\\buttons\\settingsButton.png", *new Vector2f(300, 900));

            if (x3.isMouseOver(window, 0)) {
                Vector2f pos = x3.sprite.getPosition();
                x3.sprite.setScale(1.05, 1.05);
                x3.sprite.setPosition(pos.x - 5, pos.y - 5);
            }
            else if (x4.isMouseOver(window, 0)) {
                Vector2f pos = x4.sprite.getPosition();
                x4.sprite.setScale(1.05, 1.05);
                x4.sprite.setPosition(pos.x - 5, pos.y - 5);
            }
            else if (x5.isMouseOver(window, 0)) {
                Vector2f pos = x5.sprite.getPosition();
                x5.sprite.setScale(1.05, 1.05);
                x5.sprite.setPosition(pos.x - 5, pos.y - 5);
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
                else if (set.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; state = 6;
                }
            }
            window.draw(rect);
            window.draw(x3.sprite);
            window.draw(x4.sprite);
            window.draw(x5.sprite);
            window.draw(textChoose.sprite);
            window.draw(set.sprite);
        }
        if (isGame) {
            Object buttonRestart = *new Object("src\\buttons\\restart.png", *new Vector2f(870, 40));
            Object buttonExit = *new Object("src\\buttons\\home.png", *new Vector2f(770, 40));
            Object upArrow = *new Object("src\\buttons\\upArrow.png", *new Vector2f(450, 670));
            Object downArrow = *new Object("src\\buttons\\downArrow1.png", *new Vector2f(450, 800));
            Object leftArrow = *new Object("src\\buttons\\leftArrow1.png", *new Vector2f(320, 735));
            Object rightArrow = *new Object("src\\buttons\\rightArrow1.png", *new Vector2f(580, 735));
            
            if (!isWinner && !isGameOver)
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
            cout << state << endl;

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
                    firstMove = true;
                }
                else if (Keyboard::isKeyPressed(Keyboard::A)) {
                    keyPressed = true;
                    if (MoveLeft(nums, CURRENT_RESULT))
                        newRandNum(nums);
                    firstMove = true;
                }
                else if (Keyboard::isKeyPressed(Keyboard::S)) {
                    keyPressed = true;
                    if (MoveDown(nums, CURRENT_RESULT))
                        newRandNum(nums);
                    firstMove = true;
                }
                else if (Keyboard::isKeyPressed(Keyboard::W)) {
                    keyPressed = true;
                    if (MoveUp(nums, CURRENT_RESULT))
                        newRandNum(nums);
                    firstMove = true;
                }

            }



            if (Mouse::isButtonPressed(Mouse::Left) && !buttonPressed && !isGameOver) {
                buttonPressed = true;
                if (buttonRestart.isMouseOver(window, 0)) {
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow; firstMove = false;
                }
                else if (buttonExit.isMouseOver(window, 0)) {
                    writeToFileResults(CURRENT_RESULT);
                    transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow; firstMove = false;
                }
                else if (upArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveUp(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        firstMove = true;
                    }
                }
                else if (leftArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveLeft(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        firstMove = true;
                    }
                }
                else if (rightArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveRight(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        firstMove = true;
                    }
                }
                else if (downArrow.isMouseOver(window, 0)) {
                    {
                        if (MoveDown(nums, CURRENT_RESULT))
                            newRandNum(nums);
                        firstMove = true;
                    }
                }
                
            }
            showCurrentResult(window, CURRENT_RESULT, BEST_RESULT);

            if (isGameOver || isWinner) {

                // GENERATING TEXT
                Object textGameOver("src\\buttons\\over.png", *new Vector2f(150, 50));
                Font font;
                font.loadFromFile("ofont.ru_Bowler.ttf");
                RectangleShape rect;
                rect.setSize(*new Vector2f(1000, 1000));
                rect.setFillColor(*new Color(255, 255, 255, 230));
                Object restart("src\\buttons\\snachala.png", *new Vector2f(200, 600));
                Object toMenu("src\\buttons\\menu.png", *new Vector2f(380, 780));
                if (restart.isMouseOver(window, 0)) {
                    Vector2f pos = restart.sprite.getPosition();
                    restart.sprite.setScale(*new Vector2f(1.025, 1.025));
                    restart.sprite.setPosition(*new Vector2f(pos.x-5, pos.y-5));
                }
                if (toMenu.isMouseOver(window, 0)) {
                    Vector2f pos = toMenu.sprite.getPosition();
                    toMenu.sprite.setScale(*new Vector2f(1.05, 1.05));
                    toMenu.sprite.setPosition(*new Vector2f(pos.x - 5, pos.y - 5));
                }
                

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (restart.isMouseOver(window, 0)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = gameWindow;
                    }
                    else if (toMenu.isMouseOver(window, 0)) {
                        writeToFileResults(CURRENT_RESULT);
                        transition = true; transitionStart = clock.getElapsedTime().asSeconds(); windowType = menuWindow;
                    }
                }


                window.draw(rect);
                window.draw(restart.sprite);
                window.draw(toMenu.sprite);
                window.draw(textGameOver.sprite);
            }
        }
        if (transition) {
            int duration = 2;
            writeToFileResults(CURRENT_RESULT);
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
                    case settingsWindow: { isSettings = true;break; }
                    case menuWindow: { isMenu = true; break; }
                    case gameWindow: { 
                        isGame = true;
                        if (fstart) {
                            nums = genNums(state);
                            genFnum(nums);
                            fstart = false;
                           
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

