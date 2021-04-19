#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Centipede.h"
#include "Blaster.h"
#include "Mushroom.h"

#define SCENE_W 800;
#define SCENE_H 600;

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    void showMainMenu();
    ~Game();
private:
    QGraphicsScene * scene;
    Centipedes *centipedes;
    Blaster *blaster;
    MushroomField *mushrooms;
public slots:
    void start();

signals:

};

#endif // GAME_H
