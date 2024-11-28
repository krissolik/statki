#include "board.h"
#include <iostream>

using namespace std;

// Konstruktor planszy - inicjalizuje wszystkie komorki jako wode
Board::Board() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = WATER; // Ustawienie wszystkich komorek jako woda
        }
    }
}

// Funkcja pomocnicza sprawdzająca, czy dany segment statku nie jest otoczony innymi segmentami
bool Board::isPositionValid(int x, int y) const {
    // Sprawdzanie wszystkich sąsiednich komorek w obrebie 1 pola wokol (x, y)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newX = x + i;
            int newY = y + j;

            // Upewnij sie, ze wspolrzedne są w zakresie planszy
            if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
                if (grid[newX][newY] == SHIP_SYMBOL) {
                    return false; // Znaleziono inny segment statku w sąsiedztwie
                }
            }
        }
    }
    return true; // Brak sąsiednich segmentow statkow
}

// Funkcja umieszczająca statek na planszy
bool Board::placeShip(const Ship& ship) {
    // Sprawdzanie, czy statek miesci sie w granicach planszy
    for (int i = 0; i < ship.length; ++i) {
        int newX = ship.x;
        int newY = ship.y;

        // Oblicz nową wspolrzedną w zaleznosci od kierunku
        switch (ship.direction) {
            case 'u': newX -= i; break; // Gora
            case 'd': newX += i; break; // Dol
            case 'l': newY -= i; break; // Lewo
            case 'r': newY += i; break; // Prawo
            default:
                cout << "Podano niepoprawny kierunek!" << endl;
                return false;
        }

        // Sprawdź, czy nowa wspolrzedna miesci sie w granicach planszy
        if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10) {
            cout << "Statek wykracza poza granice planszy!" << endl;
            return false;
        }

        // Sprawdź, czy miejsce jest wolne od innych statkow
        if (!isPositionValid(newX, newY)) {
            cout << "Statek nie moze stykać sie z innym statkiem." << endl;
            return false;
        }
    }

    // Jesli wszystkie sprawdzenia zostaly spelnione, umiesć statek
    for (int i = 0; i < ship.length; ++i) {
        int newX = ship.x;
        int newY = ship.y;

        switch (ship.direction) {
            case 'u': newX -= i; break; // Gora
            case 'd': newX += i; break; // Dol
            case 'l': newY -= i; break; // Lewo
            case 'r': newY += i; break; // Prawo
        }

        grid[newX][newY] = SHIP_SYMBOL; // Oznacz pole jako zajete przez statek
    }
    return true;
}

// Funkcja wyswietlająca plansze
void Board::display(bool showShips) {
    cout << endl;
    cout << "   ";
    for (int i = 0; i < 10; ++i) cout << i + 1 << " "; 
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        if(i < 9)
            cout << i + 1 << "  "; 
        if(i == 9) 
            cout << i + 1 << " ";
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == SHIP_SYMBOL && !showShips)
                cout << WATER << " "; // Ukrywanie statkow przeciwnika
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Funkcja sprawdzająca, czy statek jest zatopiony
bool Board::isShipSunk(int x, int y) {
    char direction[] = {-1, 1, 0, 0}; // Sprawdzaj w gore, dol, lewo i prawo
    char orientation[] = {0, 0, -1, 1};
    
    // Sprawdzaj w czterech kierunkach od pozycji trafienia
    for (int d = 0; d < 4; ++d) {
        int newX = x, newY = y;
        // Poruszaj sie w danym kierunku, sprawdzając ciąglosć statku
        while (newX >= 0 && newX < 10 && newY >= 0 && newY < 10 && 
               (grid[newX][newY] == HIT || grid[newX][newY] == SHIP_SYMBOL)) {
            if (grid[newX][newY] == SHIP_SYMBOL) {
                return false; // Jesli znajdziemy nienaruszoną czesć statku, statek nie jest zatopiony
            }
            newX += direction[d];
            newY += orientation[d];
        }
    }
    return true; // Wszystkie czesci są trafione
}

// Funkcja wykonująca strzal
bool Board::takeShot(int x, int y) {
    if (x < 0 || x >= 10 || y < 0 || y >= 10) {
        cout << "Nieprawidlowe wspolrzedne!" << endl << "podaj je ponownie" <<endl;;
        return true;
    }

    if (grid[x][y] == SHIP_SYMBOL) {
        grid[x][y] = HIT; // Trafienie
        cout << "Trafiony!" << endl;

        if (isShipSunk(x, y)) {
            cout << "Trafiony, zatopiony!" << endl;
        }
        return true;
    } else if (grid[x][y] == WATER) {
        grid[x][y] = MISS; // Pudlo
        cout << "Pudlo!" << endl;
        return false;
    } else {
        cout << "Juz strzelales w to miejsce." << endl;
        return false;
    }
}

// Funkcja sprawdzająca, czy wszystkie statki zostaly zatopione
bool Board::allShipsSunk() const {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == SHIP_SYMBOL) return false;
        }
    }
    return true;
}
