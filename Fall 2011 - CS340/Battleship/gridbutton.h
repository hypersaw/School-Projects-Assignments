#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QPushButton>
#include <QIcon>
#include <QMouseEvent>
#include "square.h"
#include "board.h"
#include "mainwindow.h"
#include "gameinfo.h"

class MainWindow;
class Board;
class Square;
class GameInfo;

class GridButton : public QPushButton{
    Q_OBJECT

public:
    GridButton(int x, int y, QWidget *parent = 0);
    void setSquare(Square * square);
    void mouseReleaseEvent(QMouseEvent *e);
    static MainWindow * mainwindow;
    static GameInfo * currentGame;
    static Board * boardPlayer;
    static Board * boardOpponent;
    static QIcon icon_water[2];
    static QIcon icon_hit[2];
    static QIcon icon_hship[5];
    static QIcon icon_vship[5];
    static QIcon icon_hhship[3];
    static QIcon icon_hvship[3];

private:
    Square * square;
    int x, y;
};

inline void GridButton::setSquare(Square *square){
    this->square = square;
}

#endif // GRIDBUTTON_H
