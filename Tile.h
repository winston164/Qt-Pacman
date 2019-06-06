#ifndef TILE_H
#define TILE_H
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

class Game;
class Tile: public QGraphicsRectItem{
public:
    Tile();
    Tile(Game*);

    void setPallet(bool power);
    void setNode(QString s);
    void eat();
    void setWall();
    bool isWall();
    bool isNode();
private:
    bool Wall;
    bool Eaten;
    bool PowerPallet;
    bool Node;
    QGraphicsEllipseItem *pallet;
    Game *game;
};

#endif // TILE_H
