#include "Centipede.h"
#include "Dart.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QList>

#include <QDebug>

//-------------------------------------------
//          Centipede Definitions
//-------------------------------------------

// Constructor
// Create a centipede and start movement timer
Centipede::Centipede(int len, int x, int y, int speed, bool direction)
{
    // Create centipede
    length = len;
    this->direction = direction;
    for (int i = 0; i < length; i++) {

        Centipede_Segment *segment;
        if (i == length - 1)
           segment = new Centipede_Segment(false, direction);
        else
           segment = new Centipede_Segment(true, direction);

        // Starting position depends on direction
        if (direction)
            segment->setPos(x+25*i,y);
        else
            segment->setPos(x-25*i,y);

        segments.push_back(segment);
    }

    // Connect to timer
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // Start timer
    timer->start(speed);

    // Centipede is not intially turning
    turning = -1;
}

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

// Move the centipede
void Centipede::move()
{    

    bool turned = false;

    // Moving right
    if (direction) {

        // Move each segment individually
        for (int i = 0; i < length; i++) {
            Centipede_Segment *segment = segments[i];

            // Not turning
            if (turning == -1) {

                // Done turning, move left to complete loop
                if (!direction) {
                    segment->setPos(segment->x()-25, segment->y());
                }

                // Not turning yet, move right
                else if (segment->pos().x() < 775) {
                    segment->setPos(segment->x()+25, segment->y());
                }

                // Has reached wall, start the turn
                else {
                    turning = length - 2;
                    segment->setPos(segment->x(), segment->y()+25);
                    segment->set_head(!direction);

                    // If length is 1, turning is complete
                    if (turning == -1) {
                        direction = false;
                    }
                }
            }
            else {
                // If segment not yet to wall, move right
                if (i < turning) {
                    segment->setPos(segment->x()+25, segment->y());
                }
                // If segment has already turned, move left
                else if (i > turning) {
                    segment->setPos(segment->x()-25, segment->y());
                }
                // If segment is currently turning, move it down
                else {
                    turning -= 1;
                    segment->setPos(segment->x(), segment->y() + 25);

                    // Done turning, mark direction change
                    if (turning == -1) {
                        direction = false;
                    }
                }
            }
        }
    }

    // Moving left
    else {

        // Move each segment individually
        for (int i = length -1; i >= 0; i--) {
            Centipede_Segment *segment = segments[i];

            // Moving left, not turning
            if (turning == -1) {
                if (segment->pos().x() > 0) {
                    segment->setPos(segment->x()-25, segment->y());
                }
                // Has reached wall, start the turn
                else {
                    turning = length - 2;
                    turned = true;
                    segment->setPos(segment->x(), segment->y()+25);
                    segment->set_head(!direction);

                    // If length is 1, turning is complete
                    if (turning == -1) {
                        direction = true;
                    }
                }
            }
            else {
                // If segment not yet to wall, move left
                if (i > turning) {
                    segment->setPos(segment->x()+25, segment->y());
                }
                // If segment has already turned, move left
                else if (i < turning) {
                    segment->setPos(segment->x()-25, segment->y());
                }
                // If segment is currently turning, move it down
                else if (!turned){
                    turning -= 1;
                    turned = true;
                    segment->setPos(segment->x(), segment->y() + 25);

                    // Done turning, mark direction change
                    if (turning == -1) {
                        direction = true;
                    }
                }

                // If it's the segments turn to turn, but not until next loop,
                // move it left
                else {
                    segment->setPos(segment->x()-25, segment->y());
                    turned = false;
                }
            }
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


// Returns true if the current segment was shot
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
Centipedes::Centipedes(QGraphicsScene *scene)
{
    // Start a single centipede
    Centipede *centipede = new Centipede(12, 0, 100, 150, true);
    centipedes.push_back(centipede);
    centipede->addToScene(scene);

    this->scene = scene;
}


// TO-DO: pretty sure calling this will crash it
Centipedes::~Centipedes()
{
    int length = centipedes.size();
    for (int i = length - 1; i >= 0; i--) {
        delete centipedes.back();
        centipedes.pop_back();
    }
}

// Checks all centipedes for collision with dart
// and adjusts centipede accordingly
void Centipedes::collision_check()
{
    std::vector<int> deleting;
    for (int i = 0; i < int(centipedes.size()); i++) {
        for (int j = 0; j < int(centipedes[i]->segments.size()); j++) {

            // Handle collision with dart
            if (centipedes[i]->segments[j]->is_shot()) {

                // Get length of centipede
                int length = centipedes[i]->segments.size();

                //TO-DO: turn segments into mushrooms instead of deleting them

                // If there is only one segment in centipede, delete centipede
                if (length == 1) {
                    deleting.push_back(i);
                }

                // If this segment is the head, delete the segment
                // and convert first body segment into head
                else if (j == length - 1) {
                    scene->removeItem(centipedes[i]->segments[j]);
                    centipedes[i]->segments.pop_back();
                    centipedes[i]->segments.back()->set_head(centipedes[i]->direction);
                    centipedes[i]->length-=1;
                }

                // If this segment is the tail, delete the segment
                else if (j == 0) {
                    scene->removeItem(centipedes[i]->segments[j]);
                    centipedes[i]->segments.erase(centipedes[i]->segments.begin());
                    centipedes[i]->length-=1;
                }

                // If this segment is in the middle of the centipede,
                // delete the segment and separate the centipede into two
                else {

                    // Mark centipede for deletion
                    deleting.push_back(i);

                    // Create new centipedes
                    Centipede *new_cent;

                    new_cent = new Centipede(j, centipedes[i]->segments.front()->x(), centipedes[i]->segments.front()->y(), 110, centipedes[i]->direction);
                    centipedes.push_back(new_cent);
                    new_cent->addToScene(scene);

                    new_cent = new Centipede(length - j - 1, centipedes[i]->segments[j+1]->x(), centipedes[i]->segments[j+1]->y(), 110, centipedes[i]->direction);
                    centipedes.push_back(new_cent);
                    new_cent->addToScene(scene);
                }

                break;

            }
        }
    }

    // For any scenes marked for deletiong, remove from scene
    // and delete from centipedes vector
    for (int i = int(deleting.size()) - 1; i >= 0; i--) {
        Centipede * temp = centipedes[deleting[i]];
        for (int j = 0; j < int(temp->segments.size()); j++) {
            scene->removeItem(temp->segments[j]);
        }
        centipedes.erase(centipedes.begin()+deleting[i]);
        delete temp;
    }
}
