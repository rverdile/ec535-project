#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#define FIELD_W 800
#define FIELD_H 550
#define FULL_W 800
#define FULL_H 700

class Mushroom: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Mushroom(); // single mushroom object
    int getHealth(); // return current health of mushroom
    bool decrementHealth(); // decrease health by 1
    bool is_shot();
private:
    int health = 4;
};

class MushroomField: public QObject, QGraphicsPixmapItem{
    Q_OBJECT
public:
    MushroomField(int num_mushrooms, QGraphicsScene * myscene);
    std::vector<Mushroom *> mushroom_field;
    int binary_field[FULL_W/25][FULL_H/25] = {};
public slots:
    void dartCollision();
private:
    int num_mushrooms;
    QGraphicsScene * myscene;
};

#endif // MUSHROOM_H