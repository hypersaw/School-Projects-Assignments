/*
 * The code is written by:
 *     Andrew Long (along27)
 *     Chung-Lun Chiang (cchian5)
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBitmap>
#include <QMainWindow>
#include <QTimer>
#include <QAbstractButton>
#include <QPixmap>
#include <QMessageBox>
#include <QTableWidget>
#include <QDialog>
#include <QVector>
#include <QPair>
#include <QFile>
#include <QInputDialog>
#include <QTextStream>
#include <QCoreApplication>
#include "minebutton.h"
#include "board.h"

const int MAPSIZE = 10;
const int MINENUM = 10;

class MineButton;
class Board;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setClick();
    void startTimer();
    void gameOver(bool win = false);
    void displayMineNumber(int mineNumber);
    explicit MainWindow(QWidget *parent = 0);
    static bool rankingSorting(const QPair<QString,int>& e1, const QPair<QString,int>& e2);
    ~MainWindow();

public slots:
    void gameStart();
    void quitSlot();
    void aboutSlot();
    void helpSlot();
    void topTenSlot();
    void clearTopTenSlot();
    void update();


private:
    Ui::MainWindow *ui;
    bool firstClick;
    int timerCount;
    QTimer *timer;
    MineButton * mb[MAPSIZE][MAPSIZE];
    Board * board;
    QVector < QPair<QString, int> > ranking;
    void initRanking();
    bool newRecord();
};

#endif // MAINWINDOW_H
