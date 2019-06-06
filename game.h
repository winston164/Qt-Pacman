#ifndef GAME_H
#define GAME_H
#include "Tile.h"
#include "GameEntity.h"
#define SCORE_PADDING 80
#define GRID_W 28
#define GRID_H 31
#define GRID_SCALE 20
#include <QGraphicsSceneEvent>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


class Game:public QGraphicsScene{

    Q_OBJECT

public:
    Game();
    Tile * getTileXY(int x, int y);
    void addPoints(int p, bool pallet);
    void powerPallet();
    void GameOver();
    std::vector<GameEntity *> entities;
    bool power;

public slots:
    void play();
    void normalMode();
    void scatter();

private:

    int pallets;
    int points;
    bool gg;
    QTimer * scattert;
    QGraphicsTextItem * dashboard;
    std::vector<Tile *> nodes;
    std::vector<Tile *> tiles;
    //std::vector<GameEntity *> entities;
    QGraphicsPixmapItem *board;
};

#endif // GAME_H
