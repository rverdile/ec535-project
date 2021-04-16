#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "centipede.h"
#include "Blaster.h"

#define SCENE_W 800;
#define SCENE_H 600;

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    ~Game();
private:
    QGraphicsScene * scene;
    Centipedes *centipedes;
    Blaster *blaster;

signals:

};

#endif // GAME_H
