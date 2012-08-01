/*
 * The code is written by:
 *     Andrew Long (along27)
 *     Chung-Lun Chiang (cchian5)
 */
#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QMouseEvent>
#include "mainwindow.h"
#include "square.h"
#include "board.h"

class MainWindow;
class Board;
class Square;

class MineButton : public QPushButton
{
    Q_OBJECT

private:
    Square * square;
    int x;
    int y;

public:
    static QIcon icon_flag;
    static QIcon icon_blank;
    static QIcon icon_mine;
    static QIcon icon_check;
    static QIcon icon_flagmine;
    static QIcon icon_number[9];
    static MainWindow * mainwindow;
    static Board * board;
    MineButton (int x, int y, QWidget *parent = 0);
    ~MineButton();
    void mouseReleaseEvent(QMouseEvent *e);
    void setSquare(Square * square);
};

inline void MineButton::setSquare(Square * square)
{
    this->square = square;
}

#endif // MINEBUTTON_H
