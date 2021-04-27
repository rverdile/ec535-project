/*
 * EC535 Final Project - Centipede
 * Mushroom: Creates and controls mushroom
 * field that the centipede navigates through
 */

#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>

class Score{
public:
    Score(QGraphicsScene *); // constructor
    QGraphicsTextItem* scoreText; // text displaying score
    long getScore(); // accessor for score
    void tailIncrease(); // increase when tail is shot
    void headIncrease(); // increase when head it shot
    void mushIncrease(); // increase when mushroom destroyed
private:
    void formatText(); // handles text formatting for score
    long score; // game score
    QGraphicsScene *scene; // pointer to main game scene

};

#endif // SCORE_H
