#include "player.h"
#include <iostream>
#include <cstdlib> // For system("cls")

using namespace std;

Player::Player(const string& playerName) : name(playerName) {}

string Player::getName() const {
    return name;
}

// Wyswietla plansze gracza, ukrywajac statki przeciwnika, jesli showShips jest false
void Player::displayBoard(bool showShips) {
    board.display(showShips);
}

void Player::placeShips() {
    // Dlugosci statkow: 4x1, 3x2, 2x3, 1x4
    int shipLengths[11] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 0}; // Dlugosci statkow
    const char* shipNames[10] = {
        "1x1 Statek", "1x1 Statek", "1x1 Statek", "1x1 Statek", 
        "2x1 Statek", "2x1 Statek", "2x1 Statek", "3x1 Statek", "3x1 Statek", 
        "4x1 Statek"
    }; // Nazwy statkow

    cout << name << ", ustaw swoje statki na planszy:" << endl;
    displayBoard(true);

    for (int i = 0; shipLengths[i] != 0; ++i) { 
        int x, y;
        char direction;
        
        cout << "Aktualnie stawiasz: " << shipNames[i] << " (dlugosc: " << shipLengths[i] << ")" << endl; // Informacja o statku

        while (true) {
            cout << "Podaj wspolrzedna X (szerokosc) dla statku " << i + 1 << " (1-" << BOARD_SIZE << "): ";
            cin >> x;
            cout << "Podaj wspolrzedna Y (wysokosc) dla statku " << i + 1 << " (1-" << BOARD_SIZE << "): ";
            cin >> y;

            // Popros o kierunek statku tylko jesli dlugosc statku jest wieksza niż 1
            if (shipLengths[i] > 1) {
                cout << "Podaj kierunek (u - gora, d - dol, l - lewo, r - prawo) dla statku " << i + 1 << ": ";
                cin >> direction;
            } else {
                direction = 'r';
            }

            // Indeksowanie od 0
            Ship newShip(y - 1, x - 1, shipLengths[i], direction);

            if (board.placeShip(newShip)) {
                cout << "Plansza po umieszczeniu statku:" << endl;
                board.display(true);
                break; // Wyjdz z petli, jesli statek zostal umieszczony
            }
        }
    }
}

void Player::takeTurn(Player& opponent) {
    int x, y;
    bool hit; // Zmienna do sprawdzenia, czy strzal byl trafiony

    cout << "Tura gracza: " << name << endl << endl;

    do {
        cout << name << ", podaj wspolrzedna X (szerokosc) do strzalu (1-" << BOARD_SIZE << "): ";
        cin >> x;

        cout << "Podaj wspolrzedna Y (wysokosc) do strzalu (1-" << BOARD_SIZE << "): ";
        cin >> y;

        // Sprawdz, czy wprowadzone wspolrzedne sa w poprawnym zakresie
        if (x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE) {
            cout << "Nieprawidlowe wspolrzedne! Sprobuj ponownie." << endl;
            continue; // Powtorz petle, nie wykonujac strzalu
        }

        hit = opponent.board.takeShot(y - 1, x - 1);

        if (hit) { 
            cout << "Twoja plansza:" << endl;
            displayBoard(true); // Wyswietlenie wlasnej planszy z widocznymi statkami
            cout << "Plansza przeciwnika po strzale:" << endl;
            opponent.displayBoard(false); // Pokazuj plansze przeciwnika bez statkow
            if (opponent.allShipsSunk()) {
                system("cls");
                break; // Zakończ gre, jesli wszystkie statki przeciwnika zostaly zatopione
            }

        } else {
            cout << "Pudlo! Tura przechodzi na drugiego gracza." << endl;
            cout << "Twoja plansza:" << endl;
            displayBoard(true); // Wyswietlenie wlasnej planszy z widocznymi statkami
            cout << "Plansza przeciwnika po strzale:" << endl;
            opponent.displayBoard(false); // Pokazuj plansze przeciwnika bez statkow
            break; // Kończymy ture, gdy gracz spudlowal
        }
    } while (hit); // Kontynuuj strzelanie, dopoki strzaly sa trafione

    if (!(opponent.allShipsSunk())) {
        char switchPlayer;
        cout << "Wprowadz dowolny przycisk, aby kontynuowac ";
        cin >> switchPlayer;
        system("cls");
        cout << "jak gracz sie przesiadl wprowadź dowolny przycisk" << endl;
        cin >> switchPlayer;

            system("cls");
    }
}

void Player::showBoard() {
    board.display(true);
}

bool Player::allShipsSunk() {
    return board.allShipsSunk();
}
