/*
*	Written by:
*	Andrew Long (along27)
*
*	November 20th 2011
*	CS 340 - Battleship
*/
#ifndef SQUARE_CLASS
#define SQUARE_CLASS
#include "gridbutton.h"
#include "gameinfo.h"

class GridButton;

class Square{
public:
    Square();
    GameInfo * currentGame;
    void showImage(int player, int playerAttacking = 0, int rand = 0);
    void changeState();                 // Change state of Square
    void setButton(GridButton * gb);    // "Connect" GridButton and Sqare
    int squareDirection;                // Direction of the ship (DO I NEED THIS?)
    int squareState;                    // Has it been shot it, if so was it a miss?
                                                        // 0 Not Shot At
                                                        // 1 Shot At/Hit
                                                        // 2 Shot At/Miss (Only applies to Water)

    char squareProperty;                // What is the square?:
                                                        // 'W' Water
                                                        // 'F' Front of Ship
                                                        // 'B' Back of Ship
                                                        // 'M' Middle of Ship

private:
    GridButton * gb;		// Pointer to Qt Button
};

inline void Square::setButton(GridButton * gb){
    this->gb = gb;
}

#endif
