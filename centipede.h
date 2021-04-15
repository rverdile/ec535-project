#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <vector>

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
    std::vector<QGraphicsRectItem *> segments;
};

#endif // CENTIPEDE_H

