#pragma once
#include "AnimationWindow.h"


class Snake {
    static constexpr int blockSize = 50;
    int len = 1;
    int moveTime = 2;
    TDT4102::Point pos = {300,300}; 

public:
    void increaseLen();
    TDT4102::Point getPosition();
    void newPosition(TDT4102::Point newPos);

};

class Apples {
        static constexpr int radius = 15;
        int numberApples = 1;
        TDT4102::Point pos;
        TDT4102::Point gridPos;

    public:
        void increseApples();
        void randomPos();
        int getRadius();
        TDT4102::Point getPosition();
        Apples genNewApple();
        TDT4102::Point getGridPos();
};