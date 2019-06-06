#include "GameEntity.h"
#include "QBrush"
#include "game.h"

GameEntity::GameEntity(){

}

GameEntity::GameEntity(Game *g): game(g),color(new QBrush(Qt::white)),dir(UP),speed(0.1){

}

void GameEntity::move(){
    this->update();
    if(dir == UP){
        this->setY(y()-speed);
    }
    if(dir == DOWN){
        this->setY(y()+speed);
    }
    if(dir == LEFT){
        if(x() > -35){
            this->setX(x()-speed);
        }else{
            setX(GRID_SCALE*GRID_W + 15);
        }
    }
    if(dir == RIGHT){
        if(x() < GRID_SCALE*GRID_W + 15){
            this->setX(x()+speed);
        }else{
            setX(-35);
        }
    }
}

void GameEntity::update(){

}

void GameEntity::changeDir(direction d){
    dir = d;
}

direction GameEntity::getDir()
{
    return dir;
}

void GameEntity::changeSpeed(double s){
    speed = s;
}

GameEntity::~GameEntity(){

}
