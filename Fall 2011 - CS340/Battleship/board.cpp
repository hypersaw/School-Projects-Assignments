#include "board.h"

Board::Board(MainWindow * mainwindow, int player){
    this->mainwindow = mainwindow;
    srand(time(NULL));

    // Create the dynamic board
    Grid = new Square* [10];
    for(int i = 0; i < 10 ; ++i)
        Grid[i] = new Square [10];

    // Initiliaze to a board of water
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            Grid[i][j].squareDirection = 0;
            //Grid[i][j].squareProperty = 'W';
            //Grid[i][j].squareState = 0;
        }
    }

    bool flagPlaced;            // Flag determines if ship has been placed
    bool flagClearPath;         // Flag determines if ships path is clear to be placed
    int Direction;              // Which direction is the ship facing?
    int placementX, placementY; // Our temporary locations for X and Y

    // Place the Aircraft Carrier
    // Since this is the first ship being placed
    // we do not need to worry if a spot is taken already
    // So many checks are skipped
    flagPlaced = false;
    while(flagPlaced == false){
        Direction = rand() % 2; // Define our ships direction
        placementX = rand() % 5;
        placementY = rand() % 5;

        if(Direction == 0){     // Horizontal Ships
            Grid[placementX][placementY].squareProperty = 'B';
            Grid[placementX+1][placementY].squareProperty = 'M';
            Grid[placementX+2][placementY].squareProperty = 'M';
            Grid[placementX+3][placementY].squareProperty = 'M';
            Grid[placementX+4][placementY].squareProperty = 'F';

            Grid[placementX][placementY].squareDirection = 1;
            Grid[placementX+1][placementY].squareDirection = 1;
            Grid[placementX+2][placementY].squareDirection = 1;
            Grid[placementX+3][placementY].squareDirection = 1;
            Grid[placementX+4][placementY].squareDirection = 1;

            flagPlaced = true;
        }
        else{
            Grid[placementX][placementY].squareProperty = 'B';
            Grid[placementX][placementY+1].squareProperty = 'M';
            Grid[placementX][placementY+2].squareProperty = 'M';
            Grid[placementX][placementY+3].squareProperty = 'M';
            Grid[placementX][placementY+4].squareProperty = 'F';

            flagPlaced = true;
        }
    }

    // Place the Battleship
    // This is our second ship, so from now on
    // we will enforce a check to make sure we will not have any colliding ships
    flagPlaced = false;
    while(flagPlaced == false){
        flagClearPath = true;
        Direction = rand() % 2; // Define our ships direction
        placementX = rand() % 6;
        placementY = rand() % 6;

        if(Direction == 0){     // Horizontal Ships

            for(int i = placementX;i < placementX+4;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[i][placementY].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX+1][placementY].squareProperty = 'M';
                Grid[placementX+2][placementY].squareProperty = 'M';
                Grid[placementX+3][placementY].squareProperty = 'F';

                Grid[placementX][placementY].squareDirection = 1;
                Grid[placementX+1][placementY].squareDirection = 1;
                Grid[placementX+2][placementY].squareDirection = 1;
                Grid[placementX+3][placementY].squareDirection = 1;

                flagPlaced = true;
            }
        }
        else{
            for(int i = placementY;i < placementY+4;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[placementX][i].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX][placementY+1].squareProperty = 'M';
                Grid[placementX][placementY+2].squareProperty = 'M';
                Grid[placementX][placementY+3].squareProperty = 'F';

                flagPlaced = true;
            }
        }
    }

    // Place the Destroyer
    flagPlaced = false;
    while(flagPlaced == false){
        flagClearPath = true;
        Direction = rand() % 2; // Define our ships direction
        placementX = rand() % 7;
        placementY = rand() % 7;

        if(Direction == 0){     // Vertical Ships

            for(int i = placementX;i < placementX+3;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[i][placementY].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX+1][placementY].squareProperty = 'M';
                Grid[placementX+2][placementY].squareProperty = 'F';

                Grid[placementX][placementY].squareDirection = 1;
                Grid[placementX+1][placementY].squareDirection = 1;
                Grid[placementX+2][placementY].squareDirection = 1;

                flagPlaced = true;
            }
        }
        else{   // Horizontal Ships

            for(int i = placementY;i < placementY+3;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[placementX][i].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX][placementY+1].squareProperty = 'M';
                Grid[placementX][placementY+2].squareProperty = 'F';

                flagPlaced = true;
            }
        }
    }

    // Place the Submarine
    flagPlaced = false;
    while(flagPlaced == false){
        flagClearPath = true;
        Direction = rand() % 2; // Define our ships direction
        placementX = rand() % 7;
        placementY = rand() % 7;

        if(Direction == 0){     // Vertical Ships

            for(int i = placementX;i < placementX+3;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[i][placementY].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX+1][placementY].squareProperty = 'M';
                Grid[placementX+2][placementY].squareProperty = 'F';

                Grid[placementX][placementY].squareDirection = 1;
                Grid[placementX+1][placementY].squareDirection = 1;
                Grid[placementX+2][placementY].squareDirection = 1;

                flagPlaced = true;
            }
        }
        else{   // Horizontal Ships

            for(int i = placementY;i < placementY+3;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[placementX][i].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX][placementY+1].squareProperty = 'M';
                Grid[placementX][placementY+2].squareProperty = 'F';

                flagPlaced = true;
            }
        }
    }

    // Place the Patrol Boat
    flagPlaced = false;
    while(flagPlaced == false){
        flagClearPath = true;
        Direction = rand() % 2; // Define our ships direction
        placementX = rand() % 8;
        placementY = rand() % 8;

        if(Direction == 0){     // Vertical Ships

            for(int i = placementX;i < placementX+2;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[i][placementY].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX+1][placementY].squareProperty = 'F';

                Grid[placementX][placementY].squareDirection = 1;
                Grid[placementX+1][placementY].squareDirection = 1;

                flagPlaced = true;
            }
        }
        else{   // Horizontal Ships

            for(int i = placementY;i < placementY+2;++i){
                // If we do not have water then something is in it's path
                // If flagClearPath has already been deactivated we won't care
                if((Grid[placementX][i].squareProperty != 'W')&&(flagClearPath == true))
                    flagClearPath = false;
            }

            if(flagClearPath){
                Grid[placementX][placementY].squareProperty = 'B';
                Grid[placementX][placementY+1].squareProperty = 'F';

                flagPlaced = true;
            }
        }
    }
}

Board::~Board()
{
    for(int i = 0; i < 10; ++i)
        delete [] Grid[i];

    delete [] Grid;
}

void Board::clickSquare(int x, int y){
    // If we have some part of a ship
    if(Grid[x][y].squareProperty != 'W' )
        Grid[x][y].squareState = 1;
    // If we have water
    if(Grid[x][y].squareProperty == 'W')
        Grid[x][y].squareState = 2;

    Grid[x][y].showImage(1,2); // Display the move
}
