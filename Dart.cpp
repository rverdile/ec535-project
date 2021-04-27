/*
 * EC535 Final Project - Centipede
 * Dart: Draws, moves, and handles collisions for
 * the dart that the player shoots at the centipedes
 */

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Dart.h"
#include "Game.h"
#include "Centipede.h"
#include "Mushroom.h"

#include <QDebug>

extern Game * game;

Dart::Dart()
{
    // Draw the dart
    setPixmap(QPixmap(":/images/images/dart.png"));

    // Connect
    QTimer * timer = new QTimer(); // every time it goes to 0, signal will execute

    // Connect timeout() function of timer to move slot of dart
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(20); // 20ms - reflects speed of dart
}

void Dart::move()
{
    // Check for collision with centipede
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++) {

        // Check for centipede collisions
        if (typeid(*(colliding_items[i])) == typeid (Centipede_Segment)) {

            // Tell centipedes that there's been a collision
            emit collision();

            // Remove dart if it collides with centipede
            scene()->removeItem(this);
            delete this;
            return;
        }

        // Check for mushroom collisions
        if (typeid(*(colliding_items[i])) == typeid (Mushroom)) {

            // Tell mushrooms there's been a collision
            emit mushroomCollision();

            // Remove dart
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // Move dart up
    setPos(x(),y()-10);

    // Remove dart if it has reached top of the screen
    if(pos().y() < 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
