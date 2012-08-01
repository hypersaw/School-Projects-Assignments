/*
*	Written by:
*	Andrew Long (along27)
*
*	November 20th 2011
*	CS 340 - Battleship
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool serverMode, QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow){
        ui->setupUi(this);
        isClient = false;
        isServer = false;
        connected = false;

        // We will now setup the connections
        QString connectionType;
        if(serverMode){
            modeServer();
            connectionType = " - Server Mode";
        }
        else{
            modeClient();
            connectionType = " - Client Mode";
        }
        setWindowTitle("Battleship" + connectionType);

        GridButton::mainwindow = this;
        boardPlayer = NULL;
        ui->gridPlayer->setSpacing(0);
        ui->gridPlayer->setMargin(0);
        ui->gridOpponent->setSpacing(0);
        ui->gridOpponent->setMargin(0);

        // ** The following will set all of our icons **
        // Check to see if our image library exists
        QFile file(":/res/image/water0.gif");
        if(!file.exists())
                QMessageBox::about(this, "Error", "Image not located.\nCopy image folder into correct directory.");

        for(int i = 0; i < 2; ++i){ // Water Types
                GridButton::icon_water[i] = QIcon(QPixmap(":/res/image/water"+QString::number(i)+".gif"));
                GridButton::icon_water[i].addPixmap(QPixmap(":/res/image/water"+QString::number(i)+".gif"),QIcon::Disabled);
        }
        for(int i = 0; i < 2; ++i){ // Hit Types
                GridButton::icon_hit[i] = QIcon(QPixmap(":/res/image/hit"+QString::number(i)+".gif"));
                GridButton::icon_hit[i].addPixmap(QPixmap(":/res/image/hit"+QString::number(i)+".gif"),QIcon::Disabled);
        }
        for(int i = 0; i < 5; ++i){ // Vertical Ships
                GridButton::icon_vship[i] = QIcon(QPixmap(":/res/image/vship"+QString::number(i)+".gif"));
                GridButton::icon_vship[i].addPixmap(QPixmap(":/res/image/vship"+QString::number(i)+".gif"),QIcon::Disabled);
        }
        for(int i = 0; i < 5; ++i){ // Horizontal Ships
                GridButton::icon_hship[i] = QIcon(QPixmap(":/res/image/hship"+QString::number(i)+".gif"));
                GridButton::icon_hship[i].addPixmap(QPixmap(":/res/image/hship"+QString::number(i)+".gif"),QIcon::Disabled);
        }
        for(int i = 0; i < 3; ++i){ // Hit Vertical Ships
                GridButton::icon_hhship[i] = QIcon(QPixmap(":/res/image/hvship"+QString::number(i)+".gif"));
                GridButton::icon_hhship[i].addPixmap(QPixmap(":/res/image/hvship"+QString::number(i)+".gif"),QIcon::Disabled);
        }
        for(int i = 0; i < 3; ++i){ // Hit Horizontal Ship
                GridButton::icon_hvship[i] = QIcon(QPixmap(":/res/image/hhship"+QString::number(i)+".gif"));
                GridButton::icon_hvship[i].addPixmap(QPixmap(":/res/image/hhship"+QString::number(i)+".gif"),QIcon::Disabled);
        }

        srand(time(NULL));
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                QSize iconSize(30, 30);

                player[i][j] = new GridButton(i, j);
                player[i][j]->setFixedSize(30, 30);
                player[i][j]->setIconSize(iconSize);
                ui->gridPlayer->addWidget(player[i][j], i, j);

                opponent[i][j] = new GridButton(i, j);
                opponent[i][j]->setFixedSize(30, 30);
                opponent[i][j]->setIconSize(iconSize);
                ui->gridOpponent->addWidget(opponent[i][j], i, j);
            }
        }
        // Connect Statements
        connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(gameStart()));
        connect(ui->actionQuit,SIGNAL(triggered()),this,SLOT(close()));
        connect(ui->buttonStatus,SIGNAL(clicked()),this,SLOT(gameSendStatusUpdate())); // Send Status Update W/Clicked
        connect(ui->buttonSendMessage,SIGNAL(clicked()),this,SLOT(gameSendMessage())); // Send Message W/Clicked
        ui->textInfoDisplay->setReadOnly(true); // Make the info field read only
        gameStart();
}

MainWindow::~MainWindow(){
    delete ui;
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            delete player[i][j];
            delete opponent[i][j];
        }
    }
}

void MainWindow::gameStart(){
    // If we were sent here from gameOver...
    if(boardPlayer != NULL){
        delete boardPlayer;
        delete boardOpponent;
        delete currentGame;
    }

    // Creat a new game instance
    srand(time(NULL)); // Seed for showImage
    currentGame = new GameInfo;
    boardPlayer = new Board(this,1);    // Player 1's board
    boardOpponent = new Board(this,2);  // Player 2's board

    if(isClient)
        currentGame->changePlayer(); // We are now player 2 if we are the client

    // Make our "connections"
    Square ** gridPlayer = boardPlayer->getGrid();
    Square ** gridOpponent = boardOpponent->getGrid();
    GridButton::boardPlayer = this->boardPlayer;
    GridButton::boardOpponent = this->boardOpponent;
    GridButton::currentGame = this->currentGame;
    boardPlayer->currentGame = this->currentGame;
    boardOpponent->currentGame = this->currentGame;

    // And display the pieces
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            // Player Grid
            player[i][j]->setSquare(&gridPlayer[i][j]);
            player[i][j]->setEnabled(false);
            gridPlayer[i][j].setButton(player[i][j]);
            gridPlayer[i][j].currentGame = this->currentGame;
            gridPlayer[i][j].showImage(1, 0, rand());


            // Opponent Grid
            opponent[i][j]->setSquare(&gridOpponent[i][j]);
            opponent[i][j]->setEnabled(false);
            gridOpponent[i][j].setButton(opponent[i][j]);
            gridOpponent[i][j].currentGame = this->currentGame;
            gridOpponent[i][j].showImage(2, 0, rand());
        }
    }

    if(isServer){
        ui->buttonStatus->setText("Waiting For Opponent");
        ui->buttonStatus->setEnabled(false);
    }
    if(isClient){
        ui->buttonStatus->setText("Ready");
        ui->buttonStatus->setEnabled(true);
    }
    updateInfo();
}

void MainWindow::gameOver(bool win){
    //Disable the game board
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j)
            opponent[i][j]->setEnabled(false);
    }

    QString gameResult;
    if(win)
        gameResult = "You win!";
    else
        gameResult = "You lost!";

    QMessageBox endGame;
    endGame.setText("Game Over, " + gameResult);
    endGame.setInformativeText("Would you like to play again?");
    endGame.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    endGame.setDefaultButton(QMessageBox::Yes);

    switch(endGame.exec()){
    case QMessageBox::Yes:
        gameStart();
        break;
    case QMessageBox::No:
        close();
        break;
    }
}

void MainWindow::updateInfo(){
    ui->lcdPlayer->display(currentGame->getRemainingShips(1));
    ui->lcdOpponent->display(currentGame->getRemainingShips(2));
    ui->labelStatsPlayer->setText(tr("Shots Fired: %1    Accuracy: %2").arg(currentGame->getShotsTotal(1)).arg(currentGame->getShotsAccuracy(1)));
    ui->labelStatsOpponent->setText(tr("Shots Fired: %1    Accuracy: %2").arg(currentGame->getShotsTotal(2)).arg(currentGame->getShotsAccuracy(2)));

    if(currentGame->getRemainingShips(1) == 0)
        gameOver(false);
    if(currentGame->getRemainingShips(2) == 0)
        gameOver(true);
}

void MainWindow::modeClient(){
    ui->textInfoDisplay->appendPlainText("--CLIENT MODE--");
    isClient = true;

    QHostAddress connectionAddress;
    quint16 connectionPort;
    //connectionAddress = QInputDialog::getText(this,"Battleship Connection Setup: Step 1","IP Address:");
    connectionPort = QInputDialog::getInt(this,"Battleship Conneciton Setup: Step 2","Port:");

    //ui->textInfoDisplay->appendPlainText(tr("<NETWORK> - Local Host Address: %1\n<NETWORK> - Port: %2").arg(gameConnection->serverAddress().toString()).arg(gameConnection->serverPort()));
    blockSize = 0;
    gameCommunication = new QTcpSocket(this);
    gameCommunication->abort(); // Clear any existing connections
    gameCommunication->connectToHost("Localhost",connectionPort); // Make our connection
    connect(gameCommunication, SIGNAL(readyRead()), this, SLOT(gameRead()));
    connected = true;
}

void MainWindow::modeServer(){
    ui->textInfoDisplay->appendPlainText("--SERVER MODE--");
    isServer = true;
    gameConnection = new QTcpServer(this);
    // If connection fails...
    if(!gameConnection->listen()){
        QMessageBox::critical(this, tr("Echo Server"),
                              tr("Unable to start the server: %1.")
                              .arg(gameConnection->errorString()));
        close();
        return;
    }
    connect(gameConnection,SIGNAL(newConnection()),this,SLOT(connectToClient()));  // New connection to client
    ui->textInfoDisplay->appendPlainText(tr("<NETWORK> - Local Host Address: %1\n<NETWORK> - Port: %2").arg(gameConnection->serverAddress().toString()).arg(gameConnection->serverPort()));
}

void MainWindow::connectToClient(){

    ui->textInfoDisplay->appendPlainText("<NETWORK> - Connected to Client");

    gameCommunication = gameConnection->nextPendingConnection();
    connect(gameCommunication,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(gameError(QAbstractSocket::SocketError)));  // If we have an error
    connect(gameCommunication,SIGNAL(disconnected()),this,SLOT(deleteLater()));                                                 // If disconnected, delete
    connect(gameCommunication,SIGNAL(readyRead()),this,SLOT(gameRead()));
    connected = true;
}

void MainWindow::gameRead(){
    QDataStream incoming(gameCommunication);
    incoming.setVersion(QDataStream::Qt_4_0);

    int type;
    incoming >> type;

    // We will also need access to player grids, so we
    // will associate those now
    Square ** gridOpponent = boardOpponent->getGrid();
    Square ** gridPlayer = boardPlayer->getGrid();

    if(type == 0){      // Status Update
        if(isServer){
            ui->buttonStatus->setText("Start Game");
            ui->buttonStatus->setEnabled(true);
        }
        else{
            for(int i = 0; i < 10; ++i){
                for(int j = 0; j < 10; ++j)
                    opponent[i][j]->setEnabled(true);
            }
            ui->buttonStatus->setText("Game in Progress");
            ui->textInfoDisplay->appendPlainText("<GAME> - The game has begun!");
            ui->textInfoDisplay->appendPlainText("<GAME> - It is your opponents turn.");
        }
    }
    else if(type == 1){ // Move
        int x,y;
        incoming >> x;
        incoming >> y;

        displayMove(x,y);
        boardPlayer->clickSquare(x,y); // Execute the move

        // Echo back to the opponent whether
        // There was a hit or not
        if(gridPlayer[x][y].squareState == 1)
            gameEcho(true,x,y);
        else
            gameEcho(false,x,y);

        updateInfo(); // Update the board info
        currentGame->changePlayer();
    }
    else if(type == 2){ // Message
        QString message;
        incoming >> message;
        ui->textInfoDisplay->appendPlainText("<CHAT> - Opponent: " + message);
    }
    else if(type == 3){ // Echo
        bool hit;
        int x,y;
        incoming >> hit;
        incoming >> x;
        incoming >> y;
        if(hit){
            gridOpponent[x][y].squareState = 1; // Set that square to Hit/Ship
            gridOpponent[x][y].showImage(2,1);
            ui->textInfoDisplay->appendPlainText("<GAME> - You hit a ship!");
        }
        else{
            gridOpponent[x][y].squareState = 2; // Set that square to Hit/Water
            gridOpponent[x][y].showImage(2,1);
            ui->textInfoDisplay->appendPlainText("<GAME> - You missed your target.");
        }

        ui->textInfoDisplay->appendPlainText("<GAME> - It is your opponents turn.");
        currentGame->changePlayer();    // Change to opponents turn
        updateInfo();                   // Update the game info, now our round is over
    }
}

void MainWindow::gameEcho(bool ship, int x, int y){
    int type = 3; // Set type to 'Echo'

    QByteArray data;
    QDataStream outgoing(&data, QIODevice::WriteOnly);
    outgoing.setVersion(QDataStream::Qt_4_0);
    outgoing << type;
    outgoing << ship;
    outgoing << x;
    outgoing << y;
    outgoing.device()->seek(0);

    gameCommunication->write(data);
}

void MainWindow::gameSendMessage(){
    QString inputText = ui->textMessageInput->text();

    // If this begins with a slash, this is a command
    // commands do not require a connection
    if(inputText[0] == '/'){

    }
    else if(connected){
        int type = 2; // Set type to 'Message'

        QByteArray data;
        QDataStream outgoing(&data, QIODevice::WriteOnly);
        outgoing.setVersion(QDataStream::Qt_4_0);
        outgoing << type;
        outgoing << ui->textMessageInput->text();
        outgoing.device()->seek(0);

        gameCommunication->write(data); // Send the message
        ui->textInfoDisplay->appendPlainText("<CHAT> - You: " + ui->textMessageInput->text()); // And put it into the display
        ui->textMessageInput->clear();  // Clear the field
    }
    else
        ui->textInfoDisplay->appendPlainText("<ERROR> - No connection! Cannot send message.");
}

void MainWindow::gameSendMove(int x, int y){
    int type = 1; // Set type to 'Move'

    QByteArray data;
    QDataStream outgoing(&data, QIODevice::WriteOnly);
    outgoing.setVersion(QDataStream::Qt_4_0);
    outgoing << type;
    outgoing << x;
    outgoing << y;
    outgoing.device()->seek(0);

    gameCommunication->write(data); // Send the message
    ui->textInfoDisplay->appendPlainText(tr("<GAME> - You attacked location [%1,%2]").arg(y).arg(x));
}

void MainWindow::gameSendStatusUpdate(){
    if(connected){
        int type = 0; // Set type to 'Status Update'

        QByteArray data;
        QDataStream outgoing(&data, QIODevice::WriteOnly);
        outgoing.setVersion(QDataStream::Qt_4_0);
        outgoing << type;
        outgoing.device()->seek(0);

        gameCommunication->write(data); // Send the message
        ui->buttonStatus->setEnabled(false);

        if(isServer){
            ui->textInfoDisplay->appendPlainText("<GAME> - The game has begun!");
            ui->textInfoDisplay->appendPlainText("<GAME> - It is your turn.");
            // Enable the playing field
            for(int i = 0; i < 10; ++i){
                for(int j = 0; j < 10; ++j)
                    opponent[i][j]->setEnabled(true);
            }
            ui->buttonStatus->setText("Game in Progress");
        }
        if(isClient)
            ui->buttonStatus->setText("Waiting for Host.");

        ui->buttonStatus->setEnabled(false);
    }
    else
        ui->textInfoDisplay->appendPlainText("<ERROR> - No connection! Cannot send status update.");
}

void MainWindow::displayMove(int y, int x){
    ui->textInfoDisplay->appendPlainText(tr("<GAME> - Your opponent has attacked coordinate [%1,%2]").arg(x).arg(y));
    ui->textInfoDisplay->appendPlainText("<GAME> - It is your turn.");
}

void MainWindow::gameError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Echo Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Echo Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Echo Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(gameCommunication->errorString()));
    }
}

