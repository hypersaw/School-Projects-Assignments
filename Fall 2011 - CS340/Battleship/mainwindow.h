#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTcpSocket>
#include <QTcpServer>
#include <QInputDialog>
#include "gridbutton.h"
#include "board.h"
#include "gameinfo.h"
#include <ctime>

class GridButton;
class Board;
class GameInfo;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool serverMode, QWidget *parent = 0);
    void updateInfo();
    ~MainWindow();

public slots:
    void gameSendStatusUpdate();
    void gameSendMessage();
    void gameSendMove(int x, int y);

private slots:
    // Network methods
    void gameRead();  // Read from socket
    void gameError(QAbstractSocket::SocketError socketError); // Connection error
    void gameEcho(bool ship, int x, int y);
    void modeServer();
    void modeClient();
    void connectToClient();

private:
    Ui::MainWindow *ui;
    GameInfo * currentGame;
    GridButton * player[10][10];
    GridButton * opponent[10][10];
    Board * boardPlayer, * boardOpponent;
    quint16 blockSize;

    bool isClient;  // Are we the client?
    bool isServer;  // Are we the server?
    bool connected; // Do we have a connection?

    void gameStart();
    void gameOver(bool win);
    void displayMove(int y, int x);

    QTcpServer * gameConnection;
    QTcpSocket * gameCommunication;
};
#endif // MAINWINDOW_H
