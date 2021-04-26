/*
 * EC535 Final Project - Centipede
 * Game: Creates the menu screens and game
 * components and handles logic for moving
 * between levels and ending the game
 */

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

#define SCENE_H 480
#define SCENE_W 272

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    ~Game();
    Score * score = nullptr;
    Centipedes *centipedes = nullptr;
private:
    QGraphicsScene * scene = nullptr;
    Blaster *blaster = nullptr;
    MushroomField *mushrooms = nullptr;
    int mushroom_color = 0;
    void removeItems();
    QTimer * timer;
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
