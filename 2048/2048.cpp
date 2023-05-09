#include"2048.h"
// чтобы сделать плавные переходы чисел можно функцию сделать только для перемещения самого числа, остальные все циклы вынести в рендер вайл

void showPlayGround()
{
    int x = 20; int y = 20;
    bool isDrawn = false;
    vector<vector<vector<int>>> nums = genNums(5);
    genFnum(nums);
    RenderWindow game(VideoMode(1000, 1000), "roma");

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

        for (int i = 0; i < size(nums); ++i) {
            for (int j = 0; j < size(nums[i]); ++j) {
                if (nums[i][j][0] != 0) {
                    Font font;
                    font.loadFromFile("CyrilicOld.ttf");
                    Text text(to_string(nums[i][j][0]), font, 40);
                    text.setFillColor(Color::Blue);
                    text.setStyle(sf::Text::Bold);
                    text.setPosition(nums[i][j][1], nums[i][j][2]);
                    game.draw(text);
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            MoveRight(nums);
            newRandNum(nums);
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            MoveLeft(nums);
            newRandNum(nums);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            MoveDown(nums);
            newRandNum(nums);
        }
        else if (Keyboard::isKeyPressed(Keyboard::W)) {
            MoveUp(nums);
            newRandNum(nums);
        }
       


        game.display();
    }
}


