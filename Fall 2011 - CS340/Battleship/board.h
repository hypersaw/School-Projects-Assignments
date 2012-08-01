/*
*	Written by:
*	Andrew Long (along27)
*
*	November 20th 2011
*	CS 340 - Battleship
*/

#ifndef BOARD_CLASS
#define BOARD_CLASS

#include "mainwindow.h"
#include "square.h"
#include "gridbutton.h"
#include "gameinfo.h"

class MainWindow;
class Square;
class GameInfo;

class Board{
public:
        Board(MainWindow * mainwindow, int player = 1);	// Initiliaze the 10x10 board
        ~Board();	// Destructor
        void clickSquare(int x, int y);
        Square ** getGrid();
        GameInfo * currentGame;

private:
        Square ** Grid;
        MainWindow * mainwindow;
};

inline Square ** Board::getGrid(){
    return Grid;
}


#endif
