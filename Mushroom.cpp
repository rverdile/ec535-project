/*
 * EC535 Final Project - Centipede
 * Mushroom: Creates and controls mushroom
 * field that the centipede navigates through
 */

#include <QKeyEvent>
#include <QGraphicsScene>
#include "Mushroom.h"
#include "Dart.h"
#include "Game.h"

#include <QDebug>

extern Game * game;

// Current mushroom ID
// 1 = purple, 2 = green, 3 = red
int mush_id = 1;

// Mushroom constructor, sets the image
Mushroom::Mushroom()
{
    getMushroomImage();
}

// Health accessor
int Mushroom::getHealth()
{
    return this->health;
}

// Decrement mushrooms health
bool Mushroom::decrementHealth()
{
    this->health--;

    // If mushroom is not destroyed, update image
    if(this->health > 0)
    {
        getMushroomImage();
        return false;
    }

    // If mushroom is destroyed, remove it
    else
    {
       scene()->removeItem(this);
       game->score->mushIncrease();
       return true;
    }
}

// Check if dart has collided with the mushroom
bool Mushroom::is_shot()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid (Dart))
        {
            return true;
        }
    }
    return false;
}

// Sets the mushrooms image based on current mush_id and health
void Mushroom::getMushroomImage()
{
    if(mush_id == 1)
    {
        if(health == 4)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_4hp.png"));
        }
        else if(health == 3)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_3hp.png"));
        }
        else if(health == 2)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_2hp.png"));
        }
        else if(health == 1)
        {
            setPixmap(QPixmap(":/images/images/purple_mush_1hp.png"));
        }
    }
    else if(mush_id == 2)
    {
        if(health == 4)
        {
            setPixmap(QPixmap(":/images/images/green_mush_4hp.png"));
        }
        else if(health == 3)
        {
            setPixmap(QPixmap(":/images/images/green_mush_3hp.png"));
        }
        else if(health == 2)
        {
            setPixmap(QPixmap(":/images/images/green_mush_2hp.png"));
        }
        else if(health == 1)
        {
            setPixmap(QPixmap(":/images/images/green_mush_1hp.png"));
        }
    }
    else if(mush_id == 3)
    {
        if(health == 4)
        {
            setPixmap(QPixmap(":/images/images/red_mush_4hp.png"));
        }
        else if(health == 3)
        {
            setPixmap(QPixmap(":/images/images/red_mush_3hp.png"));
        }
        else if(health == 2)
        {
            setPixmap(QPixmap(":/images/images/red_mush_2hp.png"));
        }
        else if(health == 1)
        {
            setPixmap(QPixmap(":/images/images/red_mush_1hp.png"));
        }
    }
}

// Mushroom field constructor
// Creates a random field with specified number of mushrooms
MushroomField::MushroomField(int num_mushrooms, QGraphicsScene * myscene)
{
    mush_id = 1;
    this->num_mushrooms = num_mushrooms;
    this->myscene = myscene;

    // Randomly generate mushroom binary field
    srand((unsigned) time(NULL));

    for(int i = 0; i < num_mushrooms; i++) {

        int x_rand = rand() % FIELD_W/16;
        int y_rand = rand() % FIELD_H/16;

        binary_field[x_rand][y_rand] = 1;

    }

    // Create mushroom objects
    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = 0; j < FIELD_H/16; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*16,32+j*16);
                mushroom_field.push_back(mushroom);
            }
        }
    }

    // Draw mushrooms
    for(size_t i = 0; i < mushroom_field.size(); i++) {
        myscene->addItem(mushroom_field[i]);
    }
}

// Handle dart collisions
void MushroomField::dartCollision()
{
    // Loop through and check all mushrooms
    for(size_t i = 0; i < mushroom_field.size(); i++)
    {
        // Check if mushroom is shot
        if(mushroom_field[i]->is_shot())
        {
            // If it is, decrement health
            if (mushroom_field[i]->decrementHealth()) {

                // Remove from binary field if mushroom is gone
                int x = mushroom_field[i]->x()/16;
                int y = mushroom_field[i]->y()/16;
                binary_field[x][y-2] = 0;
            }
        }
    }
}

// Draw mushrooms based on binary field
void MushroomField::drawField()
{
    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = 0; j < FIELD_H/16; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*16,32+j*16);
                mushroom_field.push_back(mushroom);
                myscene->addItem(mushroom);

            }
        }
    }
}

// Adds specified num mushrooms to field
void MushroomField::addMushrooms(int num)
{
    // Clear out binary field in blaster area
    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = FIELD_H/16; j < FULL_H/16; j++)
        {
            binary_field[i][j] = 0;
        }
    }

    // Randomly generated num new mushrooms
    srand((unsigned) time(NULL));

    for(int i = 0; i < num; i++) {

        int x_rand = rand() % FIELD_W/16;
        int y_rand = rand() % FIELD_H/16;

        binary_field[x_rand][y_rand] = 1;

    }

    // Creates and draws new mushrooms
    for(int i = 0; i < FIELD_W/16; i++)
    {
        for(int j = 0; j < FIELD_H/16; j++)
        {
            if(binary_field[i][j])
            {
                Mushroom * mushroom = new Mushroom();
                mushroom->setPos(i*16,32+j*16);
                mushroom_field.push_back(mushroom);
                myscene->addItem(mushroom);

            }
        }
    }
}

// Changes mushroom ID
// Used when player makes it to next level
void MushroomField::nextMushroom()
{
    if(mush_id == 1)
    {
        mush_id = 2;
    }
    else if(mush_id == 2)
    {
        mush_id = 3;
    }
    else if(mush_id == 3)
    {
        mush_id = 1;
    }
}
