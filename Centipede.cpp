/*
 * EC535 Final Project - Centipede
 * Centipede: Draws, moves, and controls the
 * centipede enemies
 */

#include "Centipede.h"
#include "Mushroom.h"
#include "Dart.h"
#include "Game.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QList>

#include <QDebug>

extern Game * game;

//-------------------------------------------
//          Centipede Definitions
//-------------------------------------------

// Constructor
// Create a centipede and start movement timer
Centipede::Centipede(int len, int x, int y, int speed, bool direction, MushroomField *mushroom_field)
{
    // Connect game ending signals
    QObject::connect(this, &Centipede::endGame_OffScreen, game, &Game::showGameEnd);

    // Save variables
    this->mushroom_field = mushroom_field;
    this->speed = speed;

    // Create centipede
    length = len;
    this->direction = direction;
    for (int i = 0; i < length; i++) {

        // Based on segment, set as head or body image
        Centipede_Segment *segment;
        if (i == length - 1)
           segment = new Centipede_Segment(false, direction);
        else
           segment = new Centipede_Segment(true, direction);

        // Starting position depends on direction
        if (direction)
            segment->setPos(x+16*i,y);
        else
            segment->setPos(x-16*i,y);

        // All segments initially move right
        segment->state = 0;

        segments.push_back(segment);
    }

    // Connect to timer
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // Start timer
    timer->start(speed);
}

// Constructor
// Only creates mushroom field and sets game ending signal
Centipede::Centipede(MushroomField *mushroom_field)
{
    this->mushroom_field = mushroom_field;
    QObject::connect(this, &Centipede::endGame_OffScreen, game, &Game::showGameEnd);
}

// Destructor
Centipede::~Centipede()
{
    for (int i = length - 1; i >= 0; i--) {
        segments.pop_back();
    }
}

// Add all centipede segments to scene
void Centipede::addToScene(QGraphicsScene * scene) {
    for (int i = 0; i < length; i++) {
        scene->addItem(segments[i]);
    }
}

// Start a centipede's movement with certain speed
void Centipede::start(int speed)
{
    // Don't let centipede go faster than 70 ms
    if (speed < 70)
        speed = 70;

    // Connect to timer
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // Start timer
    timer->start(speed);

    this->speed = speed;
}

// Change the speed of a centipede
void Centipede::update_speed(int speed)
{
    // Don't let centipede go faster than 70 ms
    if (speed < 70)
        speed = 70;

    // Update timer
    timer->setInterval(speed);
    this->speed = speed;
}

// Check if the centipede has reached the bottom of
// the screen
bool Centipede::is_Gone()
{
    int x = segments[length-1]->x();
    int y = segments[length-1]->y();

    if (y == FULL_H) {
        if (x == 0 || x >= SCENE_W - 25) {
            return true;
        }
    }
    return false;
}

// Move the centipede
void Centipede::move()
{    
    bool turn_around = false;

    // Check if centipede has reached bottom of screen
    if (is_Gone()) {

        // If it has, end the game
        emit endGame_OffScreen();
        return;
    }

    // Check if head is about to hit mushroom
    if (mushroom_collision(segments[length-1])) {
        turn_around = true;
    }

    // Move each segment of the centipede
    for (int i = 0; i < length; i++) {
        Centipede_Segment *segment = segments[i];

        // Moving right
        if (segment->state==0) {

            // If it's not the head, move it right
            if (i != length - 1) {
                 segment->setPos(segment->x()+16, segment->y());
            }
            // If it's the head
            else {
                // If not turning around, move right
                if (!turn_around) {
                    if (segment->x() < FIELD_W - 16) {
                        segment->setPos(segment->x()+16, segment->y());
                        continue;
                    }
                }
                // Otherwise, turn around
                turn_around = false;
                segment->setPos(segment->x(), segment->y()+16);
                direction = false;
                segment->state = 2;
                segment->set_head(direction);
                if (i != 0)
                    segments[i-1]->state = 1;
            }
        }

        // Turning left
        else if (segment->state == 1) {

            //Turn
            segment->setPos(segment->x(), segment->y()+16);
            segment->state = 2;

            // Set next segment to turn state
            if (i != 0)
                segments[i-1]->state = 1;

        }

        // Moving left
        else if (segment->state == 2) {

            // If it's not the head, move left
            if (i != length - 1) {
                 segment->setPos(segment->x()-16, segment->y());
            }
            // If it's the head
            else {

                // Move left if not turning
                if (!turn_around) {
                    if (segment->x() > 0) {
                        segment->setPos(segment->x()-16, segment->y());
                        continue;
                    }
                }

                // Otherwise, turn around
                turn_around = false;
                segment->setPos(segment->x(), segment->y()+16);
                direction = true;
                segment->state = 0;
                segment->set_head(direction);
                if (i != 0)
                    segments[i-1]->state = 3;
            }
        }
        // Turning right
        else if (segment->state == 3) {
            segment->setPos(segment->x() , segment->y()+16);
            segment->state = 0;
            if (i != 0)
                segments[i-1]->state = 3;
        }
    }
}

//-------------------------------------------
//       Centipede Segment Definitions
//-------------------------------------------


// Create centipede segment
// section=true -> body segment
// section=false -> head segment
Centipede_Segment::Centipede_Segment(bool section, bool direction)
{
    if (section)
        setPixmap(QPixmap(":/images/images/body.jpg"));
    else {
        if (direction)
            setPixmap(QPixmap(":/images/images/head.jpg"));
        else
            setPixmap(QPixmap(":/images/images/head_rev.jpg"));
    }
}


// Returns true if the current segment was shot by dart
bool Centipede_Segment::is_shot()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++) {
        if (typeid(*(colliding_items[i])) == typeid (Dart)) {
            return true;
        }
    }
    return false;
}

// Returns true if segment is about to hit a mushroom
bool Centipede::mushroom_collision(Centipede_Segment *segment)
{
    // Calculate position in mushroom binary field
    int x = segment->x();
    int y = segment->y();

    if (direction)
        x += 16;
    else
        x -= 16;

    x /= 16;
    y /= 16;

    // Return true if about to collide with mushroom
    if (mushroom_field->binary_field[x][y - 2]) {
        return true;
    }

    return false;
}


// Set segment as a head
void Centipede_Segment::set_head(bool direction)
{
    if (direction)
        setPixmap(QPixmap(":/images/images/head.jpg"));
    else
        setPixmap(QPixmap(":/images/images/head_rev.jpg"));
}


//-------------------------------------------
//          Centipedes Definitions
//-------------------------------------------


// Centipedes constructor
// Game starts with 1 centipede, length 12, top of screen
Centipedes::Centipedes(QGraphicsScene *scene, MushroomField *mushroom_field)
{
    // Start a single centipede
    Centipede *centipede = new Centipede(12, 0, 32, 200, true, mushroom_field);
    centipedes.push_back(centipede);
    centipede->addToScene(scene);

    this->mushroom_field = mushroom_field;
    this->scene = scene;
}

// Returns the number of active centipedes
int Centipedes::getCentipedesSize()
{
    return centipedes.size();
}

// Destructor
Centipedes::~Centipedes()
{
    int length = centipedes.size();
    for (int i = length - 1; i >= 0; i--) {
        centipedes.pop_back();
    }
}

// Stop all centipedes by stopping their movement
// timers and removing them from the centipedes vector
void Centipedes::stop()
{
    int n = (int)centipedes.size();
    for (int i = n - 1; i >= 0; i--) {
        centipedes[i]->timer->stop();
        centipedes.pop_back();
    }
}


// Checks all centipedes for collision with dart
// and adjusts centipede accordingly
void Centipedes::collision_check()
{
    std::vector<int> deleting;
    int del_num = -1;
    Centipede *del = nullptr;

    // Loop through all centipedes
    for (int i = 0; i < int(centipedes.size()); i++) {

        // Loop through all segments
        for (int j = 0; j < int(centipedes[i]->segments.size()); j++) {

            // Handle collision with dart
            if (centipedes[i]->segments[j]->is_shot()) {

                // Get length of centipede
                int length = centipedes[i]->segments.size();

                int x = centipedes[i]->segments[j]->x();
                int y = centipedes[i]->segments[j]->y();

                // Create mushroom where shot segment was
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(x,y);
                mushroom_field->mushroom_field.push_back(mushroom);
                scene->addItem(mushroom);

                x /= 16;
                y /= 16;
                mushroom_field->binary_field[x][y - 2] = 1;

                // If there is only one segment in centipede, delete centipede
                if (length == 1) {
                    game->score->headIncrease();
                    deleting.push_back(i);
                }

                // If this segment is the head, delete the segment
                // and convert first body segment into head
                else if (j == length - 1) {
                    game->score->headIncrease();
                    scene->removeItem(centipedes[i]->segments[j]);
                    centipedes[i]->segments.pop_back();
                    centipedes[i]->segments.back()->set_head(centipedes[i]->direction);
                    centipedes[i]->length-=1;
                    centipedes[i]->update_speed(centipedes[i]->speed - 20);
                }

                // If this segment is the tail, delete the segment
                else if (j == 0) {
                    game->score->tailIncrease();
                    scene->removeItem(centipedes[i]->segments[j]);
                    centipedes[i]->segments.erase(centipedes[i]->segments.begin());
                    centipedes[i]->length-=1;
                    centipedes[i]->update_speed(centipedes[i]->speed - 20);
                }

                // If this segment is in the middle of the centipede,
                // delete the segment and separate the centipede into two
                else {
                    game->score->tailIncrease();

                    // Create first new centipede
                    Centipede *new_cent = new Centipede(mushroom_field);
                    for (int k = 0; k < j; k++)
                        new_cent->segments.push_back(centipedes[i]->segments[k]);
                    new_cent->length = j;
                    if (new_cent->segments[new_cent->length-1]->state == 0)
                        new_cent->direction = true;
                    else
                        new_cent->direction = false;
                    new_cent->start(centipedes[i]->speed - 20);
                    new_cent->segments[new_cent->length - 1]->set_head(new_cent->direction);
                    centipedes.push_back(new_cent);

                    // Create second new centipede
                    new_cent = new Centipede(mushroom_field);
                    for (int k = j + 1; k < length; k++)
                        new_cent->segments.push_back(centipedes[i]->segments[k]);
                    new_cent->length = length - j - 1;
                    if (new_cent->segments[new_cent->length-1]->state == 0)
                        new_cent->direction = true;
                    else
                        new_cent->direction = false;
                    new_cent->start(centipedes[i]->speed - 20);
                    centipedes.push_back(new_cent);

                    // Set old centipede for deltion
                    del = centipedes[i];
                    scene->removeItem(centipedes[i]->segments[j]);
                    del_num = i;
                    deleting.push_back(del_num);
                }

                break;

            }
        }
    }

    // For any centipedes marked for deletion, remove from scene
    // and delete from centipedes vector
    for (int i = int(deleting.size()) - 1; i >= 0; i--) {
        if (del != nullptr && deleting[i] == del_num) {
            delete del;
            centipedes.erase(centipedes.begin()+deleting[i]);
        }
        else {
            Centipede * temp = centipedes[deleting[i]];
            for (int j = 0; j < int(temp->segments.size()); j++) {
                scene->removeItem(temp->segments[j]);
            }
            centipedes.erase(centipedes.begin()+deleting[i]);
            delete temp;
        }
    }
}
