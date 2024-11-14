#include <iostream>
#include <string>
#include "player.h"

using namespace std;

int main() {
    string p1name, p2name;
    cout << "WITAJ W GRZE W STATKI" << endl << endl;
    cout << "Oznaczenie poszczegolnych pol: " << endl;
    cout << "S - czesc statku" << endl;
    cout << "X - trafiony" << endl;
    cout << "O - pudlo" << endl;
    cout << "Podaj imie pierwszego gracza: ";
    cin >> p1name;
    cout << "Podaj imie drugiego gracza: ";
    cin >> p2name;

    int p1wins = 0;
    int p2wins = 0;

    char playAgain;
    do {
        Player player1(p1name);
        Player player2(p2name);

        // Gracz 1 ustawia swoje statki
        player1.placeShips();
        cout << "Wprowadz dowolny przycisk by kontynuowac";
        char switchPlayer;
        cin >> switchPlayer;
        
            system("cls");

        // Gracz 2 ustawia swoje statki
        player2.placeShips();
        cout << "Wprowadz dowolny przycisk by kontynuowac";
        cin >> switchPlayer;
        system("cls");


        //  tury graczy(strzelanina)
        while (true) {
            player1.takeTurn(player2);
            if (player2.allShipsSunk()) {
                cout << player1.getName() << " wygral!" << endl;
                p1wins++; // Zwiekszenie licznika wygranych gracza 1
                break;
            }
            system("cls");

            player2.takeTurn(player1);
            if (player1.allShipsSunk()) {
                cout << player2.getName() << " wygral!" << endl;
                p2wins++; // Zwiekszenie licznika wygranych gracza 2
                break;
            }
        }

        cout << "\nWyniki:\n";
        cout << p1name << ": " << p1wins << " wygrane" << endl;
        cout << p2name << ": " << p2wins << " wygrane" << endl;

        cout << "Czy chcesz zagrac ponownie? (t/n): ";
        cin >> playAgain;
        system("cls"); // Wyczysc ekran przed kolejna gra

    } while (playAgain == 't' || playAgain == 'T');

    cout << "Dziekujemy za gre!" << endl;

    char end;
    cout << "wylacz terminal wprowadzajac dowolny znak" << endl;
    cin >> end;
    return 0;
}