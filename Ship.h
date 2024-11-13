#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>

using namespace std;

class Ship {
public:
    // Constructor
    Ship(int x, int y, int length, bool horizontal);

    // Public methods
    int getX() const;               // Returns the initial X coordinate of the ship
    int getY() const;               // Returns the initial Y coordinate of the ship
    int getLength() const;          // Returns the length of the ship
    bool isHorizontal() const;      // Checks if the ship is placed horizontally
    bool hit(int position);         // Indicates if the ship is hit at the specified position
    int getHitCount() const;        // Returns the number of hit segments of the ship
    string getStatus() const;       // Returns the status of the ship (e.g., whether it's sunk)

private:
    int x, y;                       // Initial coordinates of the ship
    int length;                     // Length of the ship
    bool horizontal;                // Orientation of the ship (horizontal or vertical)
    vector<bool> hits;              // Stores information about hits on individual segments of the ship
};

#endif // SHIP_H
