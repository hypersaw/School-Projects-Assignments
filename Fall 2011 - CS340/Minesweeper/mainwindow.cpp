#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // check if image library exists
    QFile file(":/res/image/flag30.png");
    if(!file.exists())
        QMessageBox::about (this, "Error", "Image not found.\nPlease copy the image folder to where the excutable is.");

    MineButton::icon_flag = QIcon(QPixmap(":/res/image/flag30.png"));
    MineButton::icon_flag.addPixmap(QPixmap(":/res/image/flag30.png"),QIcon::Disabled);
    MineButton::icon_flagmine = QIcon(QPixmap(":/res/image/flagmine30.png"));
    MineButton::icon_flagmine.addPixmap(QPixmap(":/res/image/flagmine30.png"),QIcon::Disabled);
    MineButton::icon_blank = QIcon(QPixmap(":/res/image/blank30.png"));
    MineButton::icon_blank.addPixmap(QPixmap(":/res/image/blank30.png"),QIcon::Disabled);
    MineButton::icon_mine = QIcon(QPixmap(":/res/image/mine30.png"));
    MineButton::icon_mine.addPixmap(QPixmap(":/res/image/mine30.png"),QIcon::Disabled);
    MineButton::icon_check = QIcon(QPixmap(":/res/image/check30.png"));
    MineButton::icon_check.addPixmap(QPixmap(":/res/image/check30.png"),QIcon::Disabled);
    for(int i = 0; i <= 8; i++){
        MineButton::icon_number[i] = QIcon(QPixmap(":/res/image/num"+QString::number(i)+".png"));
        MineButton::icon_number[i].addPixmap(QPixmap(":/res/image/num"+QString::number(i)+".png"), QIcon::Disabled);
    }

    board = NULL;
    setWindowTitle("MineSweeper");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(gameStart()));
    connect(ui->action_Reset, SIGNAL(triggered()), this, SLOT(gameStart()));
    connect(ui->actionE_Xit, SIGNAL(triggered()), this, SLOT(quitSlot()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(aboutSlot()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(helpSlot()));
    connect(ui->action_Top_ten, SIGNAL(triggered()), this, SLOT(topTenSlot()));
    connect(ui->action_Clear_Top_ten, SIGNAL(triggered()), this, SLOT(clearTopTenSlot()));
    MineButton::mainwindow = this;

    ui->mapLayout->setSpacing(0);
    ui->mapLayout->setMargin(0);

    QPixmap resetButton (":/res/image/reset50.png");
    ui->resetButton->setIcon(QIcon(resetButton));
    ui->resetButton->setMask(resetButton.mask());
//    ui->resetButton->setIcon(QIcon(QPixmap(":/res/image/reset50.png")));

    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            mb[i][j] = new MineButton(i, j);
            mb[i][j]->setFixedSize(30, 30);
            QSize iconSize(30, 30);
            mb[i][j]->setIconSize(iconSize);
            mb[i][j]->setIcon(MineButton::icon_blank);

            ui->mapLayout->addWidget(mb[i][j], i, j);
        }
    }
    initRanking();
    gameStart();
}

// destructor of mainwindow
// write back the ranking data to file
MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            delete mb[i][j];
        }
    }

    QFile file("record.dat");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for(int i = 0; i < ranking.size(); i++){
        out<<ranking[i].first<<"\n";
        out<<ranking[i].second<<"\n";
    }
    file.close();
}

// determine when the timer starts
void MainWindow::setClick()
{
    ui->resetButton->setEnabled(true);
    if(firstClick == false){
        firstClick = true;
        startTimer();
    }
}

// when the reset button is pressed
void MainWindow::gameStart()
{
    if(board != NULL)
        delete board;
    ui->resetButton->setEnabled(false);

    board = new Board(MAPSIZE, MINENUM, this);
    Square ** grid = board->getGrid();
    firstClick = false;
    timer->stop();
    MineButton::board = this->board;

    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            mb[i][j]->setEnabled(true);
            mb[i][j]->setSquare(&grid[i][j]);
            mb[i][j]->setIcon(MineButton::icon_blank);
            grid[i][j].setButton(mb[i][j]);
        }
    }
    timerCount = 0;
    ui->lcdTimer->display(timerCount);
    ui->lcdMineNumber->display(board->getMineRemain());
    //
}

// clear top ten record
void MainWindow::clearTopTenSlot()
{
    ranking.clear();
}

void MainWindow::quitSlot()
{
    qApp->quit();
}

// display about dialog
void MainWindow::aboutSlot()
{
    QString s("This QT app is made by Andrew Long and Chung-Lun Chiang\n");
    s += "for CS 340: Sofware Design.";
    QMessageBox::about (this, "About", s);
}

// display top ten record
void MainWindow::topTenSlot()
{
    QDialog qd;
    // QMessageBox qb(QMessageBox::NoIcon, "Top Ten", "text", QMessageBox::Ok, this);
    QTableWidget tableWidget(&qd);
    tableWidget.setFixedSize(215, 340);
    tableWidget.setColumnCount(3);
    tableWidget.setRowCount(10);
    tableWidget.verticalHeader()->setVisible(false);
    tableWidget.horizontalHeader()->resizeSection(0, 40);
    tableWidget.horizontalHeader()->resizeSection(1, 120);
    tableWidget.horizontalHeader()->resizeSection(2, 50);
    QStringList header;
    header.append("Rank");
    header.append("Name");
    header.append("Time");
    tableWidget.setHorizontalHeaderLabels(header);
    for(int i = 0; i < 10; i++){
        QString name;
        QString time;
        if(ranking.size() > i){
            name = ranking[i].first;
            time = QString::number(ranking[i].second);
        }

        tableWidget.setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        tableWidget.setItem(i, 1, new QTableWidgetItem(name));
        tableWidget.setItem(i, 2, new QTableWidgetItem(time));
    }
    //qd.setFixedSize(500, 500);
    qd.exec();
}

// display help dialog
void MainWindow::helpSlot()
{
    QString s("Left lick on the map if there is no mine in it.\n");
    s += "The game will show you how many adjacent mines are there.\n";
    s += "If you click on a mine, you lose immediately.\n";
    s += "If you think there is a mine, just right click on it and there will be a flag.\n";
    s += "And if you are not sure, right click two times.\n";
    s += "If you want to cancel the flag, click two more times.\n";
    s += "\nYou win when you left click all the non-mine area.\n";
    QMessageBox::about (this, "Help", s);
}

// start timer
void MainWindow::startTimer()
{
    timerCount = 0;
    ui->lcdTimer->display(timerCount);
    timer->start(1000);
}

// update timer every one second
void MainWindow::update()
{
    timerCount++;
    ui->lcdTimer->display(timerCount);
}

// game ends, if the user wins, check if it's in new record
void MainWindow::gameOver(bool win)
{
    for(int i = 0; i < MAPSIZE; i++){
        for(int j = 0; j < MAPSIZE; j++){
            mb[i][j]->setEnabled(false);
        }
    }
    timer->stop();
    if(!win) // lose
    {
        QMessageBox::about (this, "Game Over", "GAME OVER!!");
    }
    else
    {
        QMessageBox::about (this, "You Win", "YOU WIN!!");
        if(newRecord()){
             bool isOK;
             QString username = QInputDialog::getText(this, "New Record",
                                "You are in top ten, please input your name:",
                                QLineEdit::Normal, "", &isOK);
             if(isOK){
                 ranking.push_back(qMakePair(username, timerCount));
                 qSort(ranking.begin(), ranking.end(), MainWindow::rankingSorting);

                 topTenSlot();
             }
        }
    }
}

// sort top ten ranking if needed
bool MainWindow::rankingSorting(const QPair<QString,int>& e1, const QPair<QString,int>& e2)
{
    if(e1.second < e2.second)
        return true;
    return false;
}

// display the remaining mine number on lcd
void MainWindow::displayMineNumber(int mineNumber)
{
    /*if(mineNumber < 0)
        ui->lcdMineNumber->display(0);
    else*/
        ui->lcdMineNumber->display(mineNumber);
}

// initialize the ranking data from file
void MainWindow::initRanking()
{
    QFile file("record.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream input(&file);
    QString buf;
    int rank = 0;
    QString status = "name";
    QString tmp_name;
    while( (buf = input.readLine()) != NULL && rank < 10){
        if(status == "name"){
            status = "time";
            tmp_name = buf;
        }else{
            status = "name";
            ranking.push_back(qMakePair(tmp_name, buf.toInt()));
            rank++;
        }
    }
    file.close();
}

// return if the user gets a new record
bool MainWindow::newRecord()
{
    if(ranking.size() < 10)
        return true;
    if(timerCount < ranking.last().second)
        return true;
    return false;
}
