#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>

// Class for centipede segment
class Centipede_Segment : public QGraphicsPixmapItem{

public:
    Centipede_Segment(bool);
};

// Class for a single centipede
class Centipede : public QObject {
    Q_OBJECT

public:
    Centipede(int len, int x, int y, int speed);
    ~Centipede();
    void addToScene(QGraphicsScene *);
public slots:
    void move();
private:
    bool direction;   // Direction of centipede movement; true=right, false=left
    int turning;      // How many segments have been turned if turning
    int length;
    std::vector<Centipede_Segment *> segments;
};


// Class for all of the centipedes
class Centipedes: public QObject {
    Q_OBJECT

public:
    Centipedes(QGraphicsScene *scene);
    ~Centipedes();
private:
    std::vector<Centipede *>centipedes;
    QGraphicsScene *scene;   // Storing scene so that future centipedes can be added later
};


#endif // CENTIPEDE_H

