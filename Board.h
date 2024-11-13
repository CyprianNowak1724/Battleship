#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Ship.h"

using namespace std;

static const char MISS_FIELD = 'O';
static const char EMPTY_FIELD = '~';
static const char SHIP_FIELD = 'S';
static const char SHOOT_FIELD = 'X';

class Board {
public:
    // Board size constant
    static const int BOARD_SIZE = 10;

    // Constructors
    Board();                                                    // Default constructor
    Board(int size);                                            // Constructor with a specified size

    // Methods for managing ships
    bool addShip(int x, int y, int length, bool horizontal);    // Add a ship to the board
    bool canPlaceShip(int x, int y, int length, bool horizontal) const; // Check if a ship can be placed
    bool allShipsSunk() const;                                  // Check if all ships have been sunk

    // Methods for attacking
    char shoot(int x, int y);                                   // Execute a shot

    // Methods for displaying the board
    void displayShips() const;                                  // Display ships
    void displayShots() const;                                  // Display hits and misses
    void display() const;                                       // Display the entire board

    // Methods for managing board state
    bool isOccupied(int x, int y) const;                        // Check if a cell is occupied
    void markHit(int x, int y);                                 // Mark a hit
    char getCell(int x, int y) const;                           // Get the value from a cell
    void setCell(int x, int y, char value);                     // Set the value in a cell
    bool sunkedShip(int i, int j);

    // Helper methods
    void markSunkShipsWithO(Board * opponentBoard);             // Mark sunk ships on the board

private:
    int size;                          // Board size
    vector<vector<char>> grid;         // Board represented as a character grid
    vector<Ship> ships;                // List of ships on the board
};

#endif // BOARD_H
