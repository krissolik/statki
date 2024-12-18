#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include "ship.h"


const char WATER = '~';
const char SHIP_SYMBOL = 'S';
const char HIT = 'X';
const char MISS = 'O';

class Board {
private:
    char grid[10][10]; // Plansza gry

    // Funkcja pomocnicza sprawdzająca, czy dany segment statku nie jest otoczony innymi segmentami
    bool isPositionValid(int x, int y) const;

public:
    Board();

    bool placeShip(const Ship& ship);

    void display(bool showShips);

    bool isShipSunk(int x, int y);

    bool takeShot(int x, int y);

    bool allShipsSunk() const;
};

#endif
