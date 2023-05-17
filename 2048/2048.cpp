//#pragma once
//#include"2048.h"
//#include"Playground.h"
//#include"Button.h"
//
//// чтобы сделать плавные переходы чисел можно функцию сделать только для перемещения самого числа, остальные все циклы вынести в рендер вайл
//
//void drawBar(RenderWindow& window, vector<int> num, int state);
//void drawPlayGround(RenderWindow& window, int state);
//void showCurrentResult(RenderWindow& window, int CURRENT_RESULT);
//void writeToFileResults(int LAST_RESULT);
//
//int play()
//{
//    int CURRENT_RESULT = 0;
//    vector<vector<vector<int>>> nums = genNums(3);
//    genFnum(nums);
//    RenderWindow game(VideoMode(1000, 1000), "Game");
//    Object bg = *new Object("src\\bg\\bg2.jpg", *new Vector2f(0, 0));
//    Button buttonExit(*new Vector2f(0, 800));
//    Button buttonRestart(*new Vector2f(500, 800));
//
//
//
//    //SETTING ICON
//    Image icon = *new Image();
//    icon.loadFromFile("src\\logo\\logo.png");
//    game.setIcon(427, 427, icon.getPixelsPtr());
//
//
//    while (game.isOpen()) {
//        Event ev;
//        while (game.pollEvent(ev)) {
//            if (ev.type == Event::Closed) {
//                game.close();
//            }
//        }
//        game.clear(Color(255, 255, 255));
//        game.draw(bg.sprite);
//        drawPlayGround(game, 3);
//        drawButton(game, buttonExit);
//        drawButton(game, buttonRestart);
//
//
//        for (int i = 0; i < size(nums); ++i) {
//            for (int j = 0; j < size(nums[i]); ++j) {
//                if (nums[i][j][0] != 0) {
//                    drawBar(game, nums[i][j], 3);
//                }
//            }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::D)) {
//            MoveRight(nums, CURRENT_RESULT);
//            newRandNum(nums);
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::A)) {
//            MoveLeft(nums, CURRENT_RESULT);
//            newRandNum(nums);
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::S)) {
//            MoveDown(nums, CURRENT_RESULT);
//            newRandNum(nums);
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::W)) {
//            MoveUp(nums, CURRENT_RESULT);
//            newRandNum(nums);
//        }
//        if (Mouse::isButtonPressed(Mouse::Left)) {
//            if (buttonRestart.isMouseOver(game)) {
//                game.close();
//                play();
//            }
//            else if (buttonExit.isMouseOver(game)) {
//                game.close();
//            }
//        }
//
//        showCurrentResult(game, CURRENT_RESULT);
//
//        game.display();
//    }
//    writeToFileResults(CURRENT_RESULT);
//    return CURRENT_RESULT;
//}
//
//
//void drawBar(RenderWindow& window, vector<int> num, int state) {
//    Image img = Image();
//    img.loadFromFile("src\\" + to_string(state) + "\\" + to_string(num[0]) + ".png");
//    Texture texture = Texture();
//    texture.loadFromImage(img);
//    Sprite sprite = Sprite();
//    sprite.setTexture(texture);
//    sprite.setPosition(*new Vector2f(num[1], num[2]));
//    window.draw(sprite);
//}
//
//void drawPlayGround(RenderWindow& window, int state) {
//    RectangleShape rect;
//    rect.setFillColor(Color::White);
//    rect.setPosition(*new Vector2f(35, 35));
//    rect.setSize(*new Vector2f(state * 204, state * 204));
//    window.draw(rect);
//}
//
//void showCurrentResult(RenderWindow& window, int CURRENT_RESULT) {
//    Font font;
//    font.loadFromFile("ofont.ru_Bowler.ttf");
//
//
//    Text number(to_string(CURRENT_RESULT), font, 40);
//    number.setFillColor(Color::Black);
//    number.setStyle(sf::Text::Bold);
//    number.setPosition(*new Vector2f(850, 220));
//
//    Text text("YOUR SCORE:", font, 25);
//    text.setFillColor(Color::Black);
//    text.setStyle(sf::Text::Bold);
//    text.setPosition(*new Vector2f(770, 185));
//
//    window.draw(number);
//    window.draw(text);
//}
//
//void drawButton(RenderWindow& window, Button& button) {
//    if (button.isMouseOver(window)) {
//        Image img = Image();
//        img.loadFromFile("src\\buttons\\button4.png");
//        Texture texture = Texture();
//        texture.loadFromImage(img);
//        Sprite sprite = Sprite();
//        sprite.setTexture(texture);
//        sprite.setPosition(button.sprite.getPosition());
//        window.draw(sprite);
//    }
//    else {
//        window.draw(button.getSprite());
//    }
//}
//
//
//
//void writeToFileResults(int LAST_RESULT) {
//    fstream file;
//    file.open("result.txt");
//    int BEST_RESULT;
//    file >> BEST_RESULT;
//    file >> BEST_RESULT;
//    file.close();
//    if (BEST_RESULT < LAST_RESULT)
//        BEST_RESULT = LAST_RESULT;
//    ofstream fout;
//    fout.open("result.txt");
//    fout << LAST_RESULT << "\n" << BEST_RESULT;
//    fout.close();
//}
//
//
//
