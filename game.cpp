#include "game.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Inky.h"
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
    gg = false;
    points = 0;
    pallets = 0;

    //Game board
    dashboard = new QGraphicsTextItem("Points: 0");
    dashboard->setDefaultTextColor(Qt::white);
    dashboard->setFont(QFont("Arial"));
    dashboard->setPos(50, 25);
    dashboard->setPlainText("Points: 0");
    this->addItem(dashboard);
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


    GameEntity * pacman = new Pacman(this);
    entities.push_back(pacman);

    GameEntity * b = new Blinky(this);
    entities.push_back(b);

    GameEntity * p = new Pinky(this);
    entities.push_back(p);

    GameEntity * c = new Clyde(this);
    entities.push_back(c);

    GameEntity * i = new Inky(this);
    entities.push_back(i);

    for(int i = 0;  i < entities.size(); i++){
        entities.at(i)->update();
    }

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));

    scattert = new QTimer();
    connect(scattert, SIGNAL(timeout()), this, SLOT(scatter()));

    timer->start(1);
    scattert->start(12000);

}

Tile * Game::getTileXY(int x, int y){
    if(x<0)x = 0;
    if(x>GRID_W) x = GRID_W;
    if(y<0)y = 0;
    if(y>GRID_H) y = GRID_H;
    return tiles.at(y*GRID_W + x);
}

void Game::addPoints(int p, bool pallet){
    points += p;
    if(pallet){
        pallets++;
    }
    QString s("Points: ");
    s.append(std::to_string(points).c_str());
    dashboard->setPlainText(s);
}

void Game::powerPallet()
{
    scattert->stop();
    for(int i = 1;  i < entities.size(); i++){
        static_cast<Ghost *>(entities.at(i))->setMode(SC);
    }
    power = true;
    QTimer::singleShot(5000, this, SLOT(normalMode()));

}

void Game::GameOver()
{
    if(gg) return;
    gg = true;
    for(unsigned i = 0;  i < entities.size(); i++){
        this->removeItem(entities.at(i));
        entities.at(i)->changeSpeed(0);
    }
    QGraphicsTextItem *t = new QGraphicsTextItem();
    t->setFont(QFont("Arial"));
    t->setPos(150, 25);
    t->setPlainText("YOU LOOSE");
    t->setDefaultTextColor(Qt::red);
    if(pallets == 246){
        t->setPlainText("YOU WIN!");
        t->setDefaultTextColor(Qt::green);
    }
    this->addItem(t);
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
scattert->start(12000);
power = false;
}

void Game::scatter(){
    for(int i = 1;  i < entities.size(); i++){
        static_cast<Ghost *>(entities.at(i))->setMode(S);
    }
    QTimer::singleShot(3000, this, SLOT(normalMode()));
}
