#pragma once
#include "AnimationWindow.h"
#include "utilities.h"
#include <vector>
#include "widgets/TextInput.h"
#include "widgets/Button.h"


class AnimationSnake : public TDT4102::AnimationWindow {
        static constexpr int blockSize = 50;
        static constexpr int startX = 200;
        static constexpr int startY = 200;
        static constexpr int numBlocksW = 8;
        std::vector<Snake> snakes;
        std::vector<Apples> apples;
        int y = blockSize;
        int x = 0;
        int score = 0;
        int snakeLenScr = 0;
        int appleScr = 0;
        TDT4102::TextInput scoreTxt;
        TDT4102::TextInput gameOverTxt;
        TDT4102::Button restartBtn;
        unsigned int framesPerTetronimoMove = 40;

    

    public:
        AnimationSnake();
        void changePosition();
        void run();
        void moveSnake();
        void drawSnake();
        void backGround();
        void drawApple();
        void collition();
        void changeLen();
        bool gameOver();
        void restart();
        bool validApple(TDT4102::Point posA);
        void changeSpeed();

};

