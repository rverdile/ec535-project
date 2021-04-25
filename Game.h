#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Centipede.h"
#include "Blaster.h"
#include "Mushroom.h"
#include "Score.h"

#define SCENE_W 800;
#define SCENE_H 600;

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    ~Game();
    Score * score = nullptr;
private:
    QGraphicsScene * scene = nullptr;
    Centipedes *centipedes = nullptr;
    Blaster *blaster = nullptr;
    MushroomField *mushrooms = nullptr;
    int mushroom_color = 0;
    void removeItems();
public slots:
    void start();
    void nextLevel();
    void showHowToPlay();
    void showMainMenu();
    void showGameEnd();
    void closeGame();
signals:

};

#endif // GAME_H
