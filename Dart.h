#ifndef DART_H
#define DART_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject> // inherit from this for signals and slots

class Dart: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT // macro for signals and slots
public:
    Dart();
public slots: // member function that can be connected to a signal
    void move();
signals:
    void collision();
    void mushroomCollision();
};

#endif // DART_H
