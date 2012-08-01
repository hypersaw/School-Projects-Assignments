#include "square.h"

Square::Square()
{
    hasMine = false;
    isFlagged = false;
    isChecked = false;
    isFlipped = false;
}

// This method will flip the square.
// That is to display the number of the adjacent mines.
void Square::flip(int minenum)
{
    isFlipped = true;
    if(minenum >= 0 && minenum <= 8){
        mb->setIcon(MineButton::icon_number[minenum]);
    }
}

// display if there is a mine
void Square::showMine()
{
    if(hasMine){
        if(isFlagged)
            mb->setIcon(MineButton::icon_flagmine);
        else
            mb->setIcon(MineButton::icon_mine);
    }
}

// handling the right click for the square
void Square::rightClick(int &m)
{
    if(isFlipped)
        return;

    if(!isFlagged && !isChecked){
        m--;
        isFlagged = true;
        mb->setIcon(MineButton::icon_flag);
    }else if(isFlagged){
        m++;
        isFlagged = false;
        isChecked = true;
        mb->setIcon(MineButton::icon_check);
    }else if(isChecked){
        isChecked = false;
        mb->setIcon(MineButton::icon_blank);
    }
}
