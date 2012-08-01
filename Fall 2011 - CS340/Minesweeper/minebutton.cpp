#include "minebutton.h"

QIcon MineButton::icon_flag;
QIcon MineButton::icon_blank;
QIcon MineButton::icon_mine;
QIcon MineButton::icon_flagmine;
QIcon MineButton::icon_check;
QIcon MineButton::icon_number[9];
MainWindow * MineButton::mainwindow;
Board * MineButton::board;

// detect mouse release
void MineButton::mouseReleaseEvent(QMouseEvent *e)
{
    mainwindow->setClick();

    if (e->button() == Qt::RightButton){
        board->rightClickSquare(x, y);
        // square->rightClick(); //setIcon(MineButton::icon_flag);
    }else if (e->button() == Qt::LeftButton){
        board->leftClickSquare(x, y);


    }
}

MineButton::MineButton(int i, int j, QWidget *parent)
    : QPushButton(parent)
{
    x = i;
    y = j;
}

MineButton::~MineButton()
{
}
