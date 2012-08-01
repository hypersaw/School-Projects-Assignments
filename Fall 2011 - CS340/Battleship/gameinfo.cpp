#include "gameinfo.h"

GameInfo::GameInfo()
{
    currentPlayer = 1;
    remainingShipsPlayer = 17;
    remainingShipsOpponent = 17;
    shotsMissedPlayer = 0;
    shotsMissedOpponent = 0;
    shotsPlayer = 0;
    shotsOpponent = 0;
}

int GameInfo::getRemainingShips(int player){
    if(player == 1)
        return remainingShipsPlayer;
    else
        return remainingShipsOpponent;
}

void GameInfo::shipHit(int player){
    if(player == 1)
        --remainingShipsPlayer;
    if(player == 2)
        --remainingShipsOpponent;
}

void GameInfo::shotsUpdate(int player, bool hit){
    if(player == 1){
        ++shotsPlayer;
        if(!hit)
            ++shotsMissedPlayer;
    }
    if(player == 2){
        ++shotsOpponent;
        if(!hit)
            ++shotsMissedOpponent;
    }
}

int GameInfo::getShotsAccuracy(int player){
    if(getShotsTotal(player) == 0)
        return 0;
    int accuracy = ((double)getShotsHit(player) / (double)getShotsTotal(player))*100;
    return accuracy;
}

int GameInfo::getShotsHit(int player){
    return (getShotsTotal(player)-getShotsMissed(player));
}

int GameInfo::getShotsMissed(int player){
    if(player == 1)
        return shotsMissedPlayer;
    else
        return shotsMissedOpponent;
}

int GameInfo::getShotsTotal(int player){
    if(player == 1)
        return shotsPlayer;
    else
        return shotsOpponent;
}
