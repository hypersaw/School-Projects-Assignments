#ifndef GAMEINFO_H
#define GAMEINFO_H

class GameInfo
{
public:
    GameInfo();

    void shipHit(int player);
    int getRemainingShips(int player);

    int getShotsTotal(int player);
    int getShotsMissed(int player);
    int getShotsHit(int player);
    int getShotsAccuracy(int player);
    void shotsUpdate(int player, bool hit);

    int getCurrentPlayer();
    void changePlayer();



private:
    int currentPlayer;
    int shotsPlayer;            // Total shots in a game - Player
    int shotsOpponent;          // Total shots in a game - Opponent
    int shotsMissedPlayer;      // Shots missed - Player
    int shotsMissedOpponent;    // Shots missed - Opponent
    int remainingShipsPlayer;
    int remainingShipsOpponent;
};

inline int GameInfo::getCurrentPlayer(){
    return currentPlayer;
}

inline void GameInfo::changePlayer(){
    if(currentPlayer == 1)
        currentPlayer = 2;
    else
        currentPlayer = 1;
}


#endif // GAMEINFO_H
