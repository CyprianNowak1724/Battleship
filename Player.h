#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Board.h"
#include "Ship.h" 

using namespace std;

class Player {
public:
    // Constants
    static const int BOARD_SIZE = 10;  // Board size
    static const int NUM_SHIPS = 5;    // Number of ships to place

    // Constructor
    Player(const string& name);
    
    ~Player();  // Destructor
    // Public methods
    bool takeTurn(Player& opponent);                // Perform a turn (attack on the opponent)
    bool allShipsSunk() const;                      // Check if all the player's ships are sunk
    string getName() const;                         // Return the player's name
    bool attack(int x, int y, Player& opponent);    // Attack on the opponent's board       
    void placeShips(Player& opponent);              // Place all ships
    void placeRandomShips();                        // Automatically place ships
    void displayBoardWithCoordinates() const;       // Display the board with coordinates
    void placeShip(int length, Player& opponent);   // Place a single ship on the board

    // Public fields
    Board* ownBoard = nullptr;       // The player's board (where ships are placed)
    Board* shotBoard = nullptr;      // The shot board (results of attacks)
    Board& getOwnBoard(); // Return a reference to the player's board


private:
    // Private fields
    string name;            // Player's name
    vector<Ship> ships;     // List of the player's ships

    // Private methods
    void updateShotBoard(int x, int y, bool hit);  // Update the shot board (hit/miss)
};

#endif // PLAYER_H
