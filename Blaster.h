/*
 * EC535 Final Project - Centipede
 * Blaster: Display and control blaster that
 * the user uses to shoot centipedes and mushrooms
 */


#ifndef BLASTER_H
#define BLASTER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#include "Centipede.h"
#include "Mushroom.h"

#define NEW_LIFE_SCORE 500
#define TIME_INVULNERABLE 2000 //ms

class Blaster: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blaster(Centipedes *, MushroomField *, QGraphicsScene * myscene);
    void keyPressEvent(QKeyEvent * event);
    QGraphicsTextItem* livesText;
public slots:
    void collisionCheck();
    void checkScore();
    void endInvulnerability();
signals:
    void endGame();
private:
    int speed = 9;
    int mov_x = 0;
    int mov_y = 0;
    int lives = 0;
    int score_int_idx = 0;
    int isInvulnerable = 0;
    Centipedes *centipedes;
    MushroomField * mushroom_field;
    QGraphicsScene * myscene;
    void placeLivesText();
};


#endif // BLASTER_H
