#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "centipede.h"
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    ~Game();
private:
    QGraphicsScene * scene;
    Centipede *centipede;

signals:

};

#endif // GAME_H
