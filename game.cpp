#include "game.h"
#include "Pacman.h"
#include "Ghost.h"
#include <string>
#include <QPixmap>
#include <QDebug>
#include <QTimer>


//constructor
Game::Game(){
    //background and bounds
    this->setSceneRect(0,0,560,700);
    this->setBackgroundBrush(Qt::black);
    power = false;
    points = 0;
    pallets = 0;

    //Game board
    board = new QGraphicsPixmapItem(
                QPixmap("../2019-pd2-pacman/Pacman_Board.png").scaled(GRID_W * GRID_SCALE, GRID_H * GRID_SCALE));
    board->setPos(0,SCORE_PADDING);
    this->addItem(board);

    //layout for tiles
    int tilesRepresentation[] = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 5, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5, 1, 1, 5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 5, 1,
      1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
      1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1,
      1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
      1, 5, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 5, 1,
      1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
      1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
      1, 5, 0, 0, 0, 0, 5, 1, 1, 5, 0, 0, 5, 1, 1, 5, 0, 0, 5, 1, 1, 5, 0, 0, 0, 0, 5, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 6, 1, 1, 6, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 6, 1, 1, 6, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 7, 6, 6, 7, 6, 6, 7, 6, 6, 7, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      6, 6, 6, 6, 6, 6, 5, 6, 6, 7, 1, 1, 1, 1, 1, 1, 1, 1, 7, 6, 6, 5, 6, 6, 6, 6, 6, 6,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1,
      1, 5, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 5, 1, 1, 5, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 5, 1,
      1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
      1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1,
      1, 5, 0, 5, 1, 1, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 1, 1, 5, 0, 5, 1,
      1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
      1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
      1, 5, 0, 5, 0, 0, 5, 1, 1, 5, 0, 0, 5, 1, 1, 5, 0, 0, 5, 1, 1, 5, 0, 0, 5, 0, 5, 1,
      1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
      1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
      1, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    //create tiles
    Tile * auxTile;
    int aux = 0;
    for(int i = 0; i < GRID_W * GRID_H; i++){
        auxTile = new Tile(this);
        auxTile->setPos(i%GRID_W * GRID_SCALE, SCORE_PADDING + (i/GRID_W * GRID_SCALE));
        switch(tilesRepresentation[i]){
        case 0://pallet
            auxTile->setPallet(false);
            break;
        case 1://wall
            auxTile->setWall();
            break;
        case 5:
            auxTile->setPallet(false);
            auxTile->setNode(QString(std::to_string(aux++).c_str()));
            nodes.push_back(auxTile);
            break;
        case 6://space
            break;
        case 7:
            auxTile->setNode(QString(std::to_string(aux++).c_str()));
            nodes.push_back(auxTile);
            break;
        case 8://power pallet
            auxTile->setPallet(true);
            break;
        }
        tiles.push_back(auxTile);
    }


    GameEntity * entity = new Pacman(this);
    entities.push_back(entity);

    Ghost * g = new Ghost(this);
    g->setPos(this->getTileXY(1,1)->pos());
    entities.push_back(g);

    for(int i = 0;  i < entities.size(); i++){
        entities.at(i)->update();
    }

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));

    timer->start(1);

}

Tile * Game::getTileXY(int x, int y){
    return tiles.at(y*GRID_W + x);
}

void Game::addPoints(int p, bool pallet){
    points += p;
    if(pallet){
        pallets++;
    }
}

void Game::powerPallet()
{
    for(int i = 1;  i < entities.size(); i++){
        static_cast<Ghost *>(entities.at(i))->setMode(SC);
    }
    power = true;
    QTimer::singleShot(3000, this, SLOT(normalMode()));

}

void Game::GameOver()
{
    if(pallets == 246){
        qDebug() << "win";
    }
}

void Game::play(){
    if(pallets >= 246)
        GameOver();
for(int i = 0;  i < entities.size(); i++){
    entities.at(i)->move();
}
}

void Game::normalMode(){
for(int i = 1;  i < entities.size(); i++){
    static_cast<Ghost *>(entities.at(i))->setMode(N);
}
power = false;
}
