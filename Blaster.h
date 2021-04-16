#ifndef BLASTER_H
#define BLASTER_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Blaster: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blaster();
    void keyPressEvent(QKeyEvent * event);
private:
    int speed = 10;
    int mov_x = 0;
    int mov_y = 0;
};


#endif // BLASTER_H
