#include <iostream>
#include <chrono>
#include <thread>
#include "Player.h"

using namespace std;

// Function to clear the console
void clearConsole() {
    this_thread::sleep_for(chrono::seconds(2)); // Pause for a moment before clearing
#ifdef _WIN32
    system("cls"); // Windows system clear command
#else
    system("clear"); // Linux/Mac system clear command
#endif
}

int main() {
    string player1Name, player2Name;

    // Input player names
    cout << "Podaj imie gracza 1: ";
    cin >> player1Name;
    cout << "Podaj imie gracza 2: ";
    cin >> player2Name;

    // Win counters
    int player1Wins = 0;
    int player2Wins = 0;

    // Game loop
    while (true) {
        Player player1(player1Name);
        Player player2(player2Name);

        // Start the game
        Player* currentPlayer = &player1;
        Player* opponentPlayer = &player2;

        // Aliases for easier access to the players' boards
        Board* currentOwnBoard = currentPlayer->ownBoard;
        Board* opponentShotBoard = opponentPlayer->shotBoard;

        Board* currentShotBoard = currentPlayer->shotBoard;
        Board* opponentPlayerShotBoard = opponentPlayer->shotBoard;

        // Placing ships for Player 1
        clearConsole();
        currentPlayer->displayBoardWithCoordinates();
        player1.placeShips(player2);

        // Placing ships for Player 2
        clearConsole();
        currentPlayer->displayBoardWithCoordinates();
        player2.placeShips(player1);

        while (true) {
            clearConsole(); // Clear the console before each turn

            // Display boards: own board and opponent's board
            currentPlayer->displayBoardWithCoordinates();

            // Player's turn: shooting at the opponent
            bool hit = currentPlayer->takeTurn(*opponentPlayer);

            // Check if all ships of the opponent are sunk
            if (opponentPlayer->allShipsSunk()) {
                cout << currentPlayer->getName() << " wygral!" << endl;

                // Update the win counters
                if (currentPlayer == &player1) {
                    player1Wins++;
                } else {
                    player2Wins++;
                }
                break; // End the game
            }

            // If it was a miss, switch to the next player
            if (!hit) {
                cout << "Pudlo! Przechodzimy do nastepnego gracza..." << endl;
                clearConsole();
                swap(currentPlayer, opponentPlayer);

                // Update the board aliases
                currentOwnBoard = currentPlayer->ownBoard;
                currentShotBoard = currentPlayer->shotBoard;
            }
        }

        // Display current results
        cout << "Aktualne wyniki:\n";
        cout << player1.getName() << ": " << player1Wins << " wygranych\n";
        cout << player2.getName() << ": " << player2Wins << " wygranych\n";

        // Ask players if they want to play again
        char playAgain;
        cout << "Czy chcesz zagrac ponownie? (t/n): ";
        cin >> playAgain;

        if (tolower(playAgain) != 't') {
            break; // End the loop if players don't want to play again
        }
    }

    return 0;
}
