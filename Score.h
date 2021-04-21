#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score{
public:
    Score();
    QGraphicsTextItem* scoreText;
    void tailIncrease(); // increase when tail is shot
    void headIncrease(); // increase when head it shot
private:
    long score;

};

#endif // SCORE_H
