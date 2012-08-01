#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Prompt the user about which mode to start in
    QMessageBox startGame;
    startGame.setText("Welcome to Battleship!");
    startGame.setInformativeText("Will you be hosting this match?");
    startGame.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    startGame.setDefaultButton(QMessageBox::No);

    bool serverMode = false;
    switch(startGame.exec()){
    case QMessageBox::Yes:
        serverMode = true;
        break;
    case QMessageBox::No:
        serverMode = false;
        break;
    }

    MainWindow w(serverMode);

    w.show();

    return a.exec();
}
