/*
 * EC535 Final Project - Centipede
 * Main Window: Creates the game
 * window and rotates it for touchscreen
 */

#include "mainwindow.h"
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <QtDebug>

Game * game;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the game window
    setWindowTitle(tr("Centipede"));
    game = new Game();
    setCentralWidget(game);
    game->show();

    // Rotate for touchscreen
    game->rotate(270);
}

MainWindow::~MainWindow()
{
    delete game;
}

