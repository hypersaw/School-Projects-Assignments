/*
 * The code is written by:
 *     Andrew Long (along27)
 *     Chung-Lun Chiang (cchian5)
 */
#ifndef SQUARE_H
#define SQUARE_H
#include "minebutton.h"

class MineButton;

class Square{
private:
    MineButton * mb;
public:
    Square();
    bool hasMine;
    bool isFlagged;	// Is it flagged?
    bool isChecked;	// Has it been checked?
    bool isFlipped;     // Is it flipped?
    void flip(int minenum);
    void setButton(MineButton * mb);
    void showMine();
    void rightClick(int &m);
};

inline void Square::setButton(MineButton *mb)
{
    this->mb = mb;
}

#endif // SQUARE_H
