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

#define NEW_LIFE_SCORE 500 // new life gained each time this score exceeded
#define TIME_INVULNERABLE 2000 //ms

class Blaster: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blaster(Centipedes *, MushroomField *, QGraphicsScene * myscene);
    void keyPressEvent(QKeyEvent * event);
    QGraphicsTextItem* livesText;
public slots:
    void collisionCheck(); // check for collision with centipede
    void checkScore(); // updates score
    void endInvulnerability(); // ends invulnerability after TIME_INVULNERABLE ends
signals:
    void endGame(); // handles death
private:
    int speed = 9; // speed blaster moves
    int mov_x = 0; // num pixels to move in x on keypress
    int mov_y = 0; // num pixels to move in y on keypress
    int lives = 0; // num of lives
    int score_int_idx = 0; // interval based on NEW_LIFE_SCORE
    int isInvulnerable = 0; // 1 if blaster in invulnerable state
    Centipedes *centipedes;
    MushroomField * mushroom_field;
    QGraphicsScene * myscene;
    void placeLivesText();
};


#endif // BLASTER_H
