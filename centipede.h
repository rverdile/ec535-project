#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>

class Centipede_Segment : public QGraphicsPixmapItem{

public:
    Centipede_Segment(bool);
};


class Centipede : public QObject {
    Q_OBJECT

public:
    Centipede();
public slots:
    void move();
    void addToScene(QGraphicsScene *);
private:
    bool direction;   // Direction of centipede movement; true=right, false=left
    int turning;      // How many segments have been turned if turning
    int length;
    bool stop;
    std::vector<Centipede_Segment *> segments;
};


#endif // CENTIPEDE_H

