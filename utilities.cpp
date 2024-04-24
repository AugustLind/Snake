#include "utilities.h"
#include "AnimationWindow.h"
#include <random>

void Snake::increaseLen(){
    len += 1;
}

void Apples::increseApples(){
    numberApples += 1;
}

TDT4102::Point Snake::getPosition(){
    return pos;
}

void Snake::newPosition(TDT4102::Point newPos){
    pos = newPos;
}

void Apples::randomPos(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,7);
    int x = distrib(gen);
    int y = distrib(gen);
    pos = {x*50 + 25, y*50 + 25};
    gridPos = {x, y};
}

int Apples::getRadius(){
    return radius;
}

TDT4102::Point Apples::getPosition(){
    return pos;
}

Apples Apples::genNewApple(){
    Apples a;
    a.randomPos();
    return a;
}

TDT4102::Point Apples::getGridPos(){
    return gridPos;
}