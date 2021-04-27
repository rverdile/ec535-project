/*
 * EC535 Final Project - Centipede
 * Mushroom: Creates and controls mushroom
 * field that the centipede navigates through
 */

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#define FIELD_W 272
#define FIELD_H 400
#define FULL_W 272
#define FULL_H 480

class Mushroom: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Mushroom(); // single mushroom object
    int getHealth(); // return current health of mushroom
    bool decrementHealth(); // decrease health by 1
    bool is_shot(); // true of mushroom collides with dart
private:
    int health = 4; // mushroom health points
    void getMushroomImage(); // draws mushroom image to screen
};

class MushroomField: public QObject, QGraphicsPixmapItem{
    Q_OBJECT
public:
    MushroomField(int num_mushrooms, QGraphicsScene * myscene);
    std::vector<Mushroom *> mushroom_field; // vector of mushrooms in field
    int binary_field[FULL_W/16][FULL_H/16] = {}; // locations of mushrooms represented with 1's
    void drawField(); // place mushrooms on screen based on binary field matrix
    void addMushrooms(int num); // add num mushrooms to field
    void nextMushroom(); // switches between purple, green, red mushrooms
public slots:
    void dartCollision(); // handles dart collision with mushroom
private:
    int num_mushrooms; // number of mushrooms in mushroom field on creation
    QGraphicsScene * myscene; // pointer to main game scene
};

#endif // MUSHROOM_H
