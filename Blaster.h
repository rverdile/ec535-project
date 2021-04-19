#ifndef BLASTER_H
#define BLASTER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#include "Centipede.h"
#include "Mushroom.h"

class Blaster: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blaster(Centipedes *, MushroomField *);
    void keyPressEvent(QKeyEvent * event);
private:
    int speed = 15;
    int mov_x = 0;
    int mov_y = 0;
    Centipedes *centipedes;
    MushroomField * mushroom_field;
};


#endif // BLASTER_H
