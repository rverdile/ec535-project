#include "centipede.h"
#include <QTimer>
#include <QGraphicsRectItem>

#include <QDebug>

Centipede::Centipede()
{
    // Draw
    length = 10;
    for (int i = 0; i < length; i++) {
        QGraphicsRectItem *segment = new QGraphicsRectItem();
        segment->setRect(0,0,20,20);
        segment->setPos(0+20*i,100);
        segments.push_back(segment);
    }

    // Connect to timer
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // Start timer
    timer->start(150);

    // Centipede direction is initially right
    direction = true;
    turning = -1;
    stop = false;

    qDebug() << "Starting centipede";
}

void Centipede::addToScene(QGraphicsScene * scene) {
    for (int i = 0; i < length; i++) {
        scene->addItem(segments[i]);
    }
}

// Move the centipede
void Centipede::move()
{
    bool turned = false;

    if (stop)
        return;

    // Moving right
    if (direction) {

        // Move each segment individually
        for (int i = 0; i < length; i++) {
            QGraphicsRectItem *segment = segments[i];
            //qDebug() << i;
            // Not turning
            if (turning == -1) {
                //qDebug() << "Moving right, not turning";

                // Done turning, move left to comlete loop
                if (!direction) {
                    segment->setPos(segment->x()-20, segment->y());
                }

                // Not turning yet, move right
                else if (segment->pos().x() < 780) {
                    segment->setPos(segment->x()+20, segment->y());
                }
                // Has reached wall, start the turn
                else {
                    turning = length - 2;
                    segment->setPos(segment->x(), segment->y()+20);
                }
            }
            else {
                // If segment not yet to wall, move right
                if (i < turning) {
                    segment->setPos(segment->x()+20, segment->y());
                }
                // If segment has already turned, move left
                else if (i > turning) {
                    segment->setPos(segment->x()-20, segment->y());
                }
                // If segment is currently turning, move it down
                else {
                    turning -= 1;
                    segment->setPos(segment->x(), segment->y() + 20);

                    // Done turning, mark direction change
                    if (turning == -1) {
                        qDebug() << "Done turning";
                        direction = false;
                    }
                }
            }
        }
    }

    // Moving left
    else {

        // Move each segment individually
        for (int i = length -1; i >= 0; i--) {
            QGraphicsRectItem *segment = segments[i];
            qDebug() << i;
            // Moving left, not turning
            if (turning == -1) {
                if (segment->pos().x() > 0) {
                    segment->setPos(segment->x()-20, segment->y());
                }
                // Has reached wall, start the turn
                else {
                    qDebug() << "Reached wall";
                    turning = length - 2;
                    turned = true;
                    segment->setPos(segment->x(), segment->y()+20);
                }
            }
            else {
                // If segment not yet to wall, move left
                if (i > turning) {
                    segment->setPos(segment->x()+20, segment->y());
                }
                // If segment has already turned, move left
                else if (i < turning) {
                    segment->setPos(segment->x()-20, segment->y());
                }
                // If segment is currently turning, move it down
                else if (!turned){
                    turning -= 1;
                    turned = true;
                    segment->setPos(segment->x(), segment->y() + 20);

                    // Done turning, mark direction change
                    if (turning == -1) {
                        qDebug() << "Done turning";
                        direction = true;
                    }
                }
                else {
                    segment->setPos(segment->x()-20, segment->y());
                    turned = false;
                }
            }
        }
    }
}
