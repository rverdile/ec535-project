#ifndef BLASTER_H
#define BLASTER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#include "Centipede.h"
#include "Mushroom.h"

#define NEW_LIFE_SCORE 100
#define TIME_INVULNERABLE 2000 //ms

class Blaster: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blaster(Centipedes *, MushroomField *);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void collisionCheck();
    void checkScore();
    void endInvulnerability();
signals:
    void endGame();
private:
    int speed = 15;
    int mov_x = 0;
    int mov_y = 0;
    int lives = 0;
    int score_int_idx = 0;
    int isInvulnerable = 0;
    Centipedes *centipedes;
    MushroomField * mushroom_field;
};


#endif // BLASTER_H
