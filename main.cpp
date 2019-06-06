#include <QApplication>
#include <QGraphicsView>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game();
    //Create view
    QGraphicsView * view = new QGraphicsView;
    view->setScene(game);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(560,700);
    view->show();
    return a.exec();
}
