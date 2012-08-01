#include "board.h"

// Dynamically create the board based on which difficulty specified
Board::Board(int size, int minenum, MainWindow * mainwindow)
{
    this->mainwindow = mainwindow;
    x = size;
    y = size;
    m = minenum;
    remain = x * y - m;

    // Create the Square array
    Grid = new Square* [x];
    for(int i = 0; i < x ; ++i)
        Grid[i] = new Square [y];

    // Start the seed for our psuedo-random number
    srand(time(NULL));

    // Populate the board with mines
    int minex, miney;
    for(int i = 0; i < m;){
        minex = rand() % x; // Choose our X cord
        miney = rand() % y;	// Choose our Y cord
        if(Grid[minex][miney].hasMine != true){
            Grid[minex][miney].hasMine = true;
            ++i;
        }
    }
}

Board::~Board()
{
    for(int i = 0; i < x; ++i)
        delete [] Grid[i];

    delete [] Grid;
}

// This will be called whenever a square is clicked
void Board::leftClickSquare(int xcord, int ycord)
{

    if(Grid[xcord][ycord].isFlagged || Grid[xcord][ycord].isChecked)
        return;

    // If the square IS NOT flagged, set isClicked to true
    // and then check the move.
    if(Grid[xcord][ycord].hasMine == true){ // game over
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                Grid[i][j].showMine();
            }
        }
        mainwindow->gameOver();
    }else if(Grid[xcord][ycord].isFlagged == false){
        checkMove(xcord, ycord);
    }
}

// This is called from clickSquare, checks surrounding squares
// for mines and will output a number (minecount) onto the square
void Board::checkMove(int xcord, int ycord)
{
    if(Grid[xcord][ycord].isFlipped)
        return;

    remain--;


    // We will now check the surrounding areas
    int minecount = 0;
    for(signed int i = -1; i < 2; ++i){
        for(signed int j = -1; j < 2; ++j){
            if(((xcord + i >= 0) && (ycord + j >= 0))
               && ((xcord + i < x) && (ycord + j < y))){
                if(Grid[xcord + i][ycord + j].hasMine == true)
                    ++minecount;
            }
        }
    }

    Grid[xcord][ycord].flip(minecount);

    if(remain == 0){
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                Grid[i][j].showMine();
            }
        }
        mainwindow->gameOver(true);
    }

    // If we have no mines surrounding us (minecount == 0)
    // then we want to check the areas surrounding us
    if(minecount == 0){
        for(signed int i = -1; i < 2; ++i){
            for(signed int j = -1; j < 2; ++j){
                if(((xcord + i >= 0) && (ycord + j >= 0))
                   && ((xcord + i < x) && (ycord + j < y))){
                    checkMove((xcord + i), (ycord + j));
                }
            }
        }
    }
}

// transfer the right click to square class
void Board::rightClickSquare(int x, int y)
{
    Grid[x][y].rightClick(m);
    mainwindow->displayMineNumber(m);
}
