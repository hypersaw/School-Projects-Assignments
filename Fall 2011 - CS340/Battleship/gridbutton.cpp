#include "gridbutton.h"

QIcon GridButton::icon_water[2];
QIcon GridButton::icon_hit[2];
QIcon GridButton::icon_hvship[3];
QIcon GridButton::icon_hhship[3];
QIcon GridButton::icon_vship[5];
QIcon GridButton::icon_hship[5];
MainWindow * GridButton::mainwindow;
Board * GridButton::boardPlayer;
Board * GridButton::boardOpponent;
GameInfo * GridButton::currentGame;

GridButton::GridButton(int i, int j, QWidget *parent) : QPushButton(parent){
    x = i;
    y = j;
}

void GridButton::mouseReleaseEvent(QMouseEvent *click){
    if(click->button() == Qt::LeftButton){
        if(currentGame->getCurrentPlayer() == 1){
            mainwindow->gameSendMove(x,y);
            setEnabled(false);           // We do not want to be able to click this again
        }
    }
}
