#include "centipede.h"
#include <QTimer>
#include <QGraphicsRectItem>

#include <QDebug>

// Constructor
// Create a centipede and start movement timer
Centipede::Centipede()
{
    // Create centipede
    length = 10;
    for (int i = 0; i < length; i++) {

        Centipede_Segment *segment;
        if (i == length - 1)
            segment = new Centipede_Segment(false);
        else
            segment = new Centipede_Segment(true);

        segment->setPos(0+25*i,100);
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

// Add all centipede segments to scene
void Centipede::addToScene(QGraphicsScene * scene) {
    for (int i = 0; i < length; i++) {
        scene->addItem(segments[i]);
    }
}

// Move the centipede
void Centipede::move()
{
    bool turned = false;

    // Moving right
    if (direction) {

        // Move each segment individually
        for (int i = 0; i < length; i++) {
            Centipede_Segment *segment = segments[i];

            // Not turning
            if (turning == -1) {

                // Done turning, move left to complete loop
                if (!direction) {
                    segment->setPos(segment->x()-25, segment->y());
                }

                // Not turning yet, move right
                else if (segment->pos().x() < 775) {
                    segment->setPos(segment->x()+25, segment->y());
                }

                // Has reached wall, start the turn
                else {
                    turning = length - 2;
                    segment->setPos(segment->x(), segment->y()+25);
                }
            }
            else {
                // If segment not yet to wall, move right
                if (i < turning) {
                    segment->setPos(segment->x()+25, segment->y());
                }
                // If segment has already turned, move left
                else if (i > turning) {
                    segment->setPos(segment->x()-25, segment->y());
                }
                // If segment is currently turning, move it down
                else {
                    turning -= 1;
                    segment->setPos(segment->x(), segment->y() + 25);

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
            Centipede_Segment *segment = segments[i];

            // Moving left, not turning
            if (turning == -1) {
                if (segment->pos().x() > 0) {
                    segment->setPos(segment->x()-25, segment->y());
                }
                // Has reached wall, start the turn
                else {
                    turning = length - 2;
                    turned = true;
                    segment->setPos(segment->x(), segment->y()+25);
                }
            }
            else {
                // If segment not yet to wall, move left
                if (i > turning) {
                    segment->setPos(segment->x()+25, segment->y());
                }
                // If segment has already turned, move left
                else if (i < turning) {
                    segment->setPos(segment->x()-25, segment->y());
                }
                // If segment is currently turning, move it down
                else if (!turned){
                    turning -= 1;
                    turned = true;
                    segment->setPos(segment->x(), segment->y() + 25);

                    // Done turning, mark direction change
                    if (turning == -1) {
                        direction = true;
                    }
                }

                // If it's the segments turn to turn, but not until next loop,
                // move it left
                else {
                    segment->setPos(segment->x()-25, segment->y());
                    turned = false;
                }
            }
        }
    }
}

// Create centipede segment
// section=true -> body segment
// section=false -> head segment
Centipede_Segment::Centipede_Segment(bool section)
{
    if (section)
        setPixmap(QPixmap(":/images/body.jpg"));
    else
        setPixmap(QPixmap(":/images/head.jpg"));
}
