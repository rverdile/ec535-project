/*
 * EC535 Final Project - Centipede
 * Dart: Draws, moves, and handles collisions for
 * the dart that the player shoots at the centipedes
 */

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
    void move(); // moves dart
signals:
    void collision(); // handles centipede collision
    void mushroomCollision(); // handles mushroom collision
};

#endif // DART_H
