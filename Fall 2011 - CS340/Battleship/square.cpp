#include "square.h"

Square::Square(){
    squareState = 0;
    squareProperty = 'W';
}

void Square::showImage(int playerBoard, int playerAttacking, int rand){
    if((playerBoard == 1 && playerAttacking == 0)||(playerBoard == 1 && playerAttacking == 2)){
        if(squareState == 0){
            if(squareProperty == 'F'){
                if(squareDirection == 1)
                    gb->setIcon(GridButton::icon_vship[4]);
                else
                    gb->setIcon(GridButton::icon_hship[4]);
            }
            if(squareProperty == 'B'){
                if(squareDirection == 1)
                    gb->setIcon(GridButton::icon_vship[0]);
                else
                    gb->setIcon(GridButton::icon_hship[0]);
            }
            if(squareProperty == 'M'){
                if(squareDirection == 1){
                    if(rand%4 == 0)
                        gb->setIcon(GridButton::icon_vship[1]);
                    else
                        gb->setIcon(GridButton::icon_vship[2]);
                }
                else{
                    if(rand%4 == 0)
                        gb->setIcon(GridButton::icon_hship[1]);
                    else
                        gb->setIcon(GridButton::icon_hship[2]);
                }
            }
            if(squareProperty == 'W'){
                if(rand%2 == 0)
                    gb->setIcon(GridButton::icon_water[1]);
                else
                    gb->setIcon(GridButton::icon_water[0]);
            }
        }
        else if(squareState == 1){
            // Decrement the players board
            currentGame->shipHit(playerBoard); // Decrement the players board
            currentGame->shotsUpdate(2,true);  // Update hit counter

            if(squareProperty == 'F'){
                if(squareDirection == 0)
                    gb->setIcon(GridButton::icon_hvship[2]);
                else
                    gb->setIcon(GridButton::icon_hhship[2]);
            }
            if(squareProperty == 'B'){
                if(squareDirection == 0)
                    gb->setIcon(GridButton::icon_hvship[0]);
                else
                    gb->setIcon(GridButton::icon_hhship[0]);
            }
            if(squareProperty == 'M'){
                if(squareDirection == 0){
                    if(rand%4 == 0)
                        gb->setIcon(GridButton::icon_hvship[1]);
                    else
                        gb->setIcon(GridButton::icon_hvship[1]);
                }
                else{
                    if(rand%4 == 0)
                        gb->setIcon(GridButton::icon_hhship[1]);
                    else
                        gb->setIcon(GridButton::icon_hhship[1]);
                }
            }
        }
        else{
            currentGame->shotsUpdate(2,false);
            gb->setIcon(GridButton::icon_hit[0]);
        }
    }
    // If we are seting up Player 2's board or if
    // Player 1 is attacking Player 2
    if((playerBoard == 2 && playerAttacking == 0)||
       (playerBoard == 2 && playerAttacking == 1)){
        if(squareState == 0){
            if(rand%2 == 0)
                gb->setIcon(GridButton::icon_water[1]);
            else
                gb->setIcon(GridButton::icon_water[0]);
        }
        else if(squareState == 1){
                currentGame->shipHit(playerBoard);
                currentGame->shotsUpdate(1,true);
                gb->setIcon(GridButton::icon_hit[1]);
            }
        else if(squareState == 2){
                currentGame->shotsUpdate(1,false);
                gb->setIcon(GridButton::icon_hit[0]);
        }
    }
}


