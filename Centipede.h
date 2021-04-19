#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <vector>
#include "Mushroom.h"

// Class for centipede segment
class Centipede_Segment : public QGraphicsPixmapItem{

public:
    Centipede_Segment(bool, bool);
    bool is_shot();
    void set_head(bool direction);
    int state = 0;     //States: 0 = moving right, 1 = turning left, 2 = moving left
                       // 3 = turning right
};

// Class for a single centipede
class Centipede : public QObject {
    Q_OBJECT

public:
    Centipede(int len, int x, int y, int speed, bool direction, MushroomField *mushroom_field);
    Centipede(MushroomField *mushroom_field);
    ~Centipede();
    void addToScene(QGraphicsScene *);
    std::vector<Centipede_Segment *> segments;
    bool direction;   // Direction of centipede movement; true=right, false=left
    int length;
    void start(int speed);
public slots:
    void move();
private:
    int turning;      // How many segments have been turned if turning
    MushroomField *mushroom_field;
    bool mushroom_collision(Centipede_Segment *segment);
};


// Class for all of the centipedes
class Centipedes: public QObject {
    Q_OBJECT

public:
    Centipedes(QGraphicsScene *scene, MushroomField *mushroom_field);
    ~Centipedes();
public slots:
    void collision_check();
private:
    std::vector<Centipede *>centipedes;
    QGraphicsScene *scene;   // Storing scene so that future centipedes can be added later
    MushroomField * mushroom_field;
};


#endif // CENTIPEDE_H

