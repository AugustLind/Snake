#include "animationSnake.h"
#include "Color.h"
#include <iostream>
#include <cmath>


AnimationSnake::AnimationSnake() : TDT4102::AnimationWindow{startX, startY, blockSize*numBlocksW, blockSize * numBlocksW + blockSize},
    scoreTxt{{0,blockSize*numBlocksW,},blockSize * 5/2,blockSize, "Score: 0"},
    gameOverTxt{{startX - blockSize,startY - blockSize},blockSize * 3,blockSize, "Game Over"},
    restartBtn{{startX - blockSize,startY + 1/2* blockSize},blockSize * 3,blockSize, "Restart"}
{
    add(scoreTxt);
    add(gameOverTxt);
    add(restartBtn);
    gameOverTxt.setVisible(false);
    restartBtn.setVisible(false);
    restartBtn.setCallback(std::bind(&AnimationSnake::restart, this));

    
}

void AnimationSnake::run(){
    unsigned int framesSinceLastTetronimoMove = 0;
    Snake a{};
    a.newPosition({blockSize*numBlocksW/2, blockSize*numBlocksW/2});
    snakes.push_back(a);
    Apples b{};
    b.randomPos();
    apples.push_back(b);
    while(!should_close()) {
        backGround();
        if (!gameOver()){ 
            framesSinceLastTetronimoMove++;
            if(framesSinceLastTetronimoMove >= framesPerTetronimoMove) {
                    framesSinceLastTetronimoMove = 0;
                    moveSnake();
                }
            changePosition();
        }
        collition();
        drawSnake();
        drawApple();
        changeLen();
        changeSpeed();
        next_frame();
    }
}


void AnimationSnake::changePosition(){
    bool wKeyIsPressed = is_key_down(KeyboardKey::W);
    bool aKeyIsPressed = is_key_down(KeyboardKey::A);
    bool sKeyIsPressed = is_key_down(KeyboardKey::S);
    bool dKeyIsPressed = is_key_down(KeyboardKey::D);
    
    if (wKeyIsPressed){
       y = -blockSize;
       x = 0;
    }

    if (sKeyIsPressed){
        y = blockSize;
        x = 0;
    }
    
    if (aKeyIsPressed){
        y = 0;
        x = -blockSize;
    }

     if (dKeyIsPressed){
        y = 0;
        x = blockSize;
    }
}

void AnimationSnake::drawSnake(){
    for (int i = 0; i < snakes.size(); i++){
        draw_rectangle(snakes.at(i).getPosition(), blockSize, blockSize, TDT4102::Color::blue);
    }
}

void AnimationSnake::moveSnake(){
    int X = x;
    int Y = y;
    for (int i = snakes.size() -1; i > 0; i--){
            snakes.at(i).newPosition(snakes.at(i-1).getPosition());
        }
    snakes.at(0).newPosition({snakes.at(0).getPosition().x + X, snakes.at(0).getPosition().y + Y});

}

void AnimationSnake::backGround(){
    TDT4102::Color color = TDT4102::Color::green_yellow;
    for (int i = 0; i < numBlocksW; i++){
        for (int j = 0; j < numBlocksW; j++){
            if ((i + j) % 2 == 0){
                color = TDT4102::Color::green_yellow;
            } else{
                color = TDT4102::Color::green;
            }
            draw_rectangle({i * blockSize, j * blockSize}, blockSize, blockSize, color);
        }
    }
}

void AnimationSnake::drawApple(){
    for (int i = 0; i < apples.size(); i++){
        draw_circle(apples.at(i).getPosition(), apples.at(i).getRadius(),TDT4102::Color::red);
    }
}

void AnimationSnake::collition(){
    int xBlocks = snakes.at(0).getPosition().x / blockSize;
    int yBlocks = snakes.at(0).getPosition().y / blockSize;
    for (int i = 0; i < apples.size(); i++){
        if(xBlocks == apples.at(i).getGridPos().x && yBlocks == apples.at(i).getGridPos().y){
            bool gyldig = false;
            Apples b{};
            while(!gyldig){
                b.randomPos();
                gyldig = validApple(b.getGridPos());
            }
            apples.at(i) = b;
            score += 1;
            snakeLenScr += 1;
            appleScr += 1;
            std::string txt = "Score: " + std::to_string(score);
            scoreTxt.setText(txt);
        }

    }
}

void AnimationSnake::changeLen(){
    if (snakeLenScr >= 1){
        snakeLenScr = 0;
        Snake a{};
        a.newPosition(snakes.back().getPosition());
        snakes.push_back(a);
    }
    if (appleScr >= 1 && apples.size() < 4){
        appleScr = 0; 
        Apples b{};
        bool gyldig = false;
        while(!gyldig){
            b.randomPos();
            gyldig = validApple(b.getGridPos());
        }
        apples.push_back(b);
    }
}

bool AnimationSnake::gameOver(){
    TDT4102::Point pos = snakes.at(0).getPosition();
    if (pos.x < 0 || pos.y < 0 || pos.x >= blockSize*numBlocksW || pos.y >= blockSize*numBlocksW){
        gameOverTxt.setVisible(true);
        restartBtn.setVisible(true);
        return true;
    }
    for (int i = 2; i < snakes.size(); i++){
        if (snakes.at(i).getPosition().x == snakes.at(0).getPosition().x && 
        snakes.at(i).getPosition().y == snakes.at(0).getPosition().y){
            gameOverTxt.setVisible(true);
            restartBtn.setVisible(true);
            return true;
        }
    }
    return false;
}

void AnimationSnake::restart(){
    snakes.clear();
    apples.clear();
    Snake a{};
    a.newPosition({blockSize*numBlocksW/2, blockSize*numBlocksW/2});
    snakes.push_back(a);
    Apples b{};
    b.randomPos();
    apples.push_back(b);        
    score = 0;
    snakeLenScr = 0;
    gameOverTxt.setVisible(false);
    restartBtn.setVisible(false);
    std::string txt = "Score: " + std::to_string(score);
    scoreTxt.setText(txt);    

}

bool AnimationSnake::validApple(TDT4102::Point posA){
    int like = 0;
    for (int j = 0; j < snakes.size(); j++){
        int xPos = snakes.at(j).getPosition().x / blockSize;
        int yPos = snakes.at(j).getPosition().y / blockSize;
        if(xPos == posA.x && yPos == posA.y){
            like += 1;
            break;
        }
    }
    for (int k = 0; k < apples.size(); k++){
        if(apples.at(k).getGridPos().x == posA.x &&  apples.at(k).getGridPos().y == posA.y){
            like += 1;
            break;
        }
    }
    if (like == 0) {
        return true;
    }
    return false;
}

void AnimationSnake::changeSpeed(){
    if (score > 10){
        framesPerTetronimoMove = 20;
    } else if (score > 5){
        framesPerTetronimoMove = 30;
    }
}