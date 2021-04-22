#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QGraphicsScene>

class Score{
public:
    Score(QGraphicsScene *);
    QGraphicsTextItem* scoreText;
    void tailIncrease(); // increase when tail is shot
    void headIncrease(); // increase when head it shot
    void mushIncrease(); // increase when mushroom destroyed
private:
    void formatText();
    long score;
    QGraphicsScene *scene;

};

#endif // SCORE_H
