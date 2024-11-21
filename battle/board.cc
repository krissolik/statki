#include "board.h"
#include <iostream>

using namespace std;

// Konstruktor planszy - inicjalizuje wszystkie komórki jako wodę
Board::Board() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            grid[i][j] = WATER; // Ustawienie wszystkich komórek jako woda
        }
    }
}

// Funkcja pomocnicza sprawdzająca, czy dany segment statku nie jest otoczony innymi segmentami
bool Board::isPositionValid(int x, int y) const {
    // Sprawdzanie wszystkich sąsiednich komórek w obrębie 1 pola wokół (x, y)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            // Upewnij się, że współrzędne są w zakresie planszy
            if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
                if (grid[newX][newY] == SHIP_SYMBOL) {
                    return false; // Znaleziono inny segment statku w sąsiedztwie
                }
            }
        }
    }
    return true; // Brak sąsiednich segmentów statków
}

// Funkcja umieszczająca statek na planszy
bool Board::placeShip(const Ship& ship) {
    for (int i = 0; i < ship.length; ++i) {
        int newX = ship.x;
        int newY = ship.y;

        switch (ship.direction) {
            case 'u': newX -= i; break; // Góra
            case 'd': newX += i; break; // Dół
            case 'l': newY -= i; break; // Lewo
            case 'r': newY += i; break; // Prawo
            default:
                cout << "Podaj ponownie kierunek" << endl; 
                return false; 
                break;
        }

        if (!isPositionValid(newX, newY)) {
            cout << "Statek nie może stykać się z innym statkiem." << endl;
            return false;
        }
    }

    // Umieszczanie statku
    for (int i = 0; i < ship.length; ++i) {
        int newX = ship.x;
        int newY = ship.y;

        // Ustawianie współrzędnych w zależności od kierunku
        switch (ship.direction) {
            case 'u': newX -= i; break; // Góra
            case 'd': newX += i; break; // Dół
            case 'l': newY -= i; break; // Lewo
            case 'r': newY += i; break; // Prawo
        }

        grid[newX][newY] = SHIP_SYMBOL; // Ustawienie symbolu statku
    }
    return true;
}

// Funkcja wyświetlająca planszę
void Board::display(bool showShips) {
    cout << endl;
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; ++i) cout << i + 1 << " "; 
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if(i < 9)
            cout << i + 1 << "  "; 
        if(i == 9) 
            cout << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (grid[i][j] == SHIP_SYMBOL && !showShips)
                cout << WATER << " "; // Ukrywanie statków przeciwnika
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Funkcja sprawdzająca, czy statek jest zatopiony
bool Board::isShipSunk(int x, int y) {
    char direction[] = {-1, 1, 0, 0}; // Sprawdzaj w górę, dół, lewo i prawo
    char orientation[] = {0, 0, -1, 1};
    
    // Sprawdzaj w czterech kierunkach od pozycji trafienia
    for (int d = 0; d < 4; ++d) {
        int newX = x, newY = y;
        // Poruszaj się w danym kierunku, sprawdzając ciągłość statku
        while (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE && 
               (grid[newX][newY] == HIT || grid[newX][newY] == SHIP_SYMBOL)) {
            if (grid[newX][newY] == SHIP_SYMBOL) {
                return false; // Jeśli znajdziemy nienaruszoną część statku, statek nie jest zatopiony
            }
            newX += direction[d];
            newY += orientation[d];
        }
    }
    return true; // Wszystkie części są trafione
}

// Funkcja wykonująca strzał
bool Board::takeShot(int x, int y) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        cout << "Nieprawidłowe współrzędne!" << endl;
        return false;
    }

    if (grid[x][y] == SHIP_SYMBOL) {
        grid[x][y] = HIT; // Trafienie
        cout << "Trafiony!" << endl;

        if (isShipSunk(x, y)) {
            cout << "Trafiony, zatopiony!" << endl;
        }
        return true;
    } else if (grid[x][y] == WATER) {
        grid[x][y] = MISS; // Pudło
        cout << "Pudło!" << endl;
        return false;
    } else {
        cout << "Już strzelałeś w to miejsce." << endl;
        return false;
    }
}

// Funkcja sprawdzająca, czy wszystkie statki zostały zatopione
bool Board::allShipsSunk() const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (grid[i][j] == SHIP_SYMBOL) return false;
        }
    }
    return true;
}
