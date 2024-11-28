#ifndef SHIP_H
#define SHIP_H

class Ship {
public:
    int x, y; // Wspolrzedne statku
    int length; // Dlugosc statku
    char direction; // Kierunek statku ('u' - gora, 'd' - dol, 'l' - lewo, 'r' - prawo)

    Ship(int xCoord, int yCoord, int shipLength, char shipDirection) 
        : x(xCoord), y(yCoord), length(shipLength), direction(shipDirection) {}
};
#endif
