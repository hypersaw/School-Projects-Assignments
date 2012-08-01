/*
 * The code is written by:
 *     Andrew Long (along27)
 *     Chung-Lun Chiang (cchian5)
 */
#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>
#include "square.h"
#include "mainwindow.h"

class MainWindow;
class Square;

class Board{
public:
    Board(int size, int minenum, MainWindow * mainwindow);    // Constructor (Easy by default)
    ~Board();                               // Desturctor
    void leftClickSquare(int x, int y);
    void rightClickSquare(int x, int y);
    void checkMove(int x, int y);
    Square ** getGrid();
    int getMineRemain();

private:
    int x, y, m;	// X cord, Y cord, how many mines
    int remain;
    Square **Grid;
    MainWindow * mainwindow;
};

inline Square ** Board::getGrid()
{
    return Grid;
}

inline int Board::getMineRemain()
{
    return m;
}

#endif // BOARD_H
