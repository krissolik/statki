#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "board.h"

class Player {
private:
    std::string name;
    Board board;

public:
    Player(const std::string& playerName);

    std::string getName() const;

    void displayBoard(bool showShips);

    void placeShips();

    void takeTurn(Player& opponent);

    void showBoard();

    bool allShipsSunk();
};

#endif
