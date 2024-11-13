#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

// Default constructor
Board::Board() : size(10), grid(size, vector<char>(size, EMPTY_FIELD)) {}

// Constructor with a specific board size
Board::Board(int size) : size(size), grid(size, vector<char>(size, EMPTY_FIELD)) {
    if (size < 1) {
        this->size = BOARD_SIZE; // Set default size
        grid.resize(this->size, vector<char>(this->size, EMPTY_FIELD));
    }
}

// Method to add a ship to the board
bool Board::addShip(int x, int y, int length, bool horizontal) {
    if (horizontal) { // Place ship horizontally
        // Check if the ship fits on the board
        if (x < 0 || x >= size || y < 0 || y >= size || x + length > size) {
            cout << "Statek nie miesci sie w granicach planszy!" << endl;
            return false;
        }

        // Check if the field is already occupied
        for (int i = 0; i < length; i++) {
            if (grid[y][x + i] != EMPTY_FIELD) {
                cout << "Pole (" << x + i << ", " << y << ") jest juz zajete!" << endl;
                return false;
            }
        }

        // Place the ship on the board
        for (int i = 0; i < length; i++) {
            grid[y][x + i] = SHIP_FIELD; // Mark the field with a ship
        }
    } else { // Place ship vertically
        // Check if the ship fits on the board
        if (x < 0 || x >= size || y < 0 || y >= size || y + length - 1 >= size) {
            cout << "Statek nie miesci sie w granicach planszy!" << endl;
            return false;
        }

        // Check if the field is already occupied
        for (int i = 0; i < length; i++) {
            if (grid[y + i][x] != EMPTY_FIELD) {
                cout << "Pole (" << x << ", " << y + i << ") jest juz zajete!" << endl;
                return false;
            }
        }

        // Place the ship on the board
        for (int i = 0; i < length; i++) {
            grid[y + i][x] = SHIP_FIELD; // Mark the field with a ship
        }
    }
    return true; // Ship was successfully placed
}

// Method to check if a field is occupied
bool Board::isOccupied(int x, int y) const {
    return grid[y][x] != EMPTY_FIELD; // If the field is not EMPTY_FIELD, it is occupied
}

// Mark a hit on the board
void Board::markHit(int x, int y) {
    if (grid[y][x] == SHIP_FIELD) {
        grid[y][x] = SHOOT_FIELD; // Mark the hit
    }
}

// Retrieve the value from a board field
char Board::getCell(int x, int y) const {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        throw out_of_range("Wspolrzedne poza zakresem planszy");
    }
    return grid[y][x];
}

// Set a value at a specific field
void Board::setCell(int x, int y, char value) {
    grid[y][x] = value; // Set the value at the specified field
}

bool Board::sunkedShip(int i, int j)
{
    for(int k = i; k >=0; k--){
        if(grid[k][j] == SHIP_FIELD){
            return false;
        }
        if(grid[k][j] == EMPTY_FIELD){
            break;
        }
    }

    for(int k = i; k < grid.size(); k++){
        if(grid[k][j] == SHIP_FIELD){
            return false;
        }
        if(grid[k][j] == EMPTY_FIELD){
            break;
        }
    }

    for(int k = j; k >=0; k--){
        if(grid[i][k] == SHIP_FIELD){
            return false;
        }
        if(grid[i][k] == EMPTY_FIELD){
            break;
        }
    }

    for(int k = j; k < grid[0].size(); k++){
        if(grid[i][k] == SHIP_FIELD){
            return false;
        }
        if(grid[i][k] == EMPTY_FIELD){
            break;
        }
    }
    return true;
}

// Mark fields around sunk ships (after hit)
void Board::markSunkShipsWithO(Board * opponentBoard) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
        if (grid[i][j] == SHOOT_FIELD) { // Ship hit
            if(opponentBoard->sunkedShip(i,j))
            {
                // Check neighboring fields
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int ni = i + dx;
                        int nj = j + dy;

                        // Check if neighboring field is within board boundaries
                        if (ni >= 0 && ni < size && nj >= 0 && nj < size) {
                            // If neighboring field is empty, mark it with MISS_FIELD
                            if (grid[ni][nj] == EMPTY_FIELD) {
                                grid[ni][nj] = MISS_FIELD;
                            }
                        }
                    }
                }
            }
        }   
    }
}
}

// Execute a shot on the board
char Board::shoot(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        cout << "Strzal poza granicami planszy!" << endl;
        return false; // Out of board boundaries
    }

    if (grid[y][x] == SHIP_FIELD) {
        grid[y][x] = SHOOT_FIELD; // Mark hit
        cout << "Trafienie!" << endl;
        return SHOOT_FIELD; // Hit
    } else if (grid[y][x] == EMPTY_FIELD) {
        grid[y][x] = MISS_FIELD; // Mark miss
        cout << "Pudlo!" << endl;
        return MISS_FIELD; // Miss
    } else {
        cout << "Juz strzelano w to miejsce!" << endl;
        return grid[y][x]; // Already shot here
    }
}

// Display only shots on the board
void Board::displayShots() const {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "  "; // Empty space in the upper left corner
            for (char c = 'A'; c < 'A' + size; c++) {
                cout << c << " "; // Display letters A-J
            }
            cout << endl;
        }
        cout << i + 1 << " "; // Display row number
        for (int j = 0; j < size; j++) {
            // Display only shots
            if (grid[i][j] == SHOOT_FIELD || grid[i][j] == MISS_FIELD) {
                cout << grid[i][j] << " "; // Hit or miss
            } else {
                cout << "~ "; // Empty field, do not display ships
            }
        }
        cout << endl; // New line after each row
    }
}

void Board::displayShips() const {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "  "; // Empty space in the upper left corner
            for (char c = 'A'; c < 'A' + size; c++) {
                cout << c << " "; // Display letters A-J
            }
            cout << endl;
        }
        cout << i + 1 << " "; // Display row number
        for (int j = 0; j < size; j++) {
            // Display only ships or empty field
            if (grid[i][j] == SHIP_FIELD) {
                cout << "S "; // Ship
            } else {
                cout << "~ "; // Empty field
            }
        }
        cout << endl; // New line after each row
    }
}

// Display the entire board with coordinates
void Board::display() const {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            cout << "   "; // Empty space in the upper left corner
            for (char c = 'A'; c < 'A' + size; c++) {
                cout << c << " "; // Display letters A-J
            }
            cout << endl;
        }
        if(i < 9)
        {
            cout << i + 1 << "  "; // Display row number
        }
        else{
            cout << i + 1 << " "; // Display row number
        }
        for (int j = 0; j < size; j++) {
            cout << grid[i][j] << " "; // Display content of the field
        }
        cout << endl; // New line after each row
    }
}


// Check if all ships are sunk
bool Board::allShipsSunk() const {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (grid[row][col] == SHIP_FIELD) {
                return false; // Found a ship, so not all ships are sunk
            }
        }
    }
    return true; // All ships are sunk
}

// Check if a ship can be placed on the board
bool Board::canPlaceShip(int x, int y, int length, bool horizontal) const {
    // Check if the ship fits within the bounds of the board
    if (horizontal) {
        if (x < 0 || y < 0 || y >= size || x + length > size) {
            return false; // Ship goes out of bounds
        }
        for (int i = 0; i < length; i++) {
            if (grid[y][x + i] != EMPTY_FIELD) {
                return false; // The space is occupied
            }
        }
        // Check the neighboring cells for horizontal placement
        for (int i = -1; i <= length; i++) {
            // Upper neighboring cells
            if (y > 0 && (x + i >= 0 && x + i < size) && grid[y - 1][x + i] != EMPTY_FIELD) {
                return false;
            }
            // Lower neighboring cells
            if (y < size - 1 && (x + i >= 0 && x + i < size) && grid[y + 1][x + i] != EMPTY_FIELD) {
                return false;
            }
        }
        // Left and right sides
        if (x > 0 && grid[y][x - 1] != EMPTY_FIELD) {
            return false;
        }
        if (x + length < size && grid[y][x + length] != EMPTY_FIELD) {
            return false;
        }
    } else { // Check for vertical placement
        if (x < 0 || y < 0 || y + length > size) {
            return false; // Ship goes out of bounds
        }
        for (int i = 0; i < length; i++) {
            if (grid[y + i][x] != EMPTY_FIELD) {
                return false; // The space is occupied
            }
        }
        // Check the neighboring cells for vertical placement
        for (int i = -1; i <= length; i++) {
            // Left side, within the board bounds
            if (x > 0 && (y + i >= 0 && y + i < size) && grid[y + i][x - 1] != EMPTY_FIELD) {
                return false;
            }
            // Right side, within the board bounds
            if (x < size - 1 && (y + i >= 0 && y + i < size) && grid[y + i][x + 1] != EMPTY_FIELD) {
                return false;
            }
        }
        // Upper neighboring cell
        if (y > 0 && grid[y - 1][x] != EMPTY_FIELD) {
            return false;
        }
        // Lower neighboring cell
        if (y + length < size && grid[y + length][x] != EMPTY_FIELD) {
            return false;
        }
    }
    return true; // Ship can be placed
}
