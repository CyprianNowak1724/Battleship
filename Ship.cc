#include "Ship.h"
#include<iostream>

using namespace std;

// Constructor definition
Ship::Ship(int x, int y, int length, bool horizontal)
    : x(x), y(y), length(length), horizontal(horizontal), hits(length, false) { // Initialize the hits vector
}

// Method definitions
int Ship::getX() const {
    return x;
}

int Ship::getY() const {
    return y;
}

int Ship::getLength() const {
    return length;
}

bool Ship::isHorizontal() const {
    return horizontal;
}

// Method to check if the ship is hit at the given position
bool Ship::hit(int position) {
    if (position >= 0 && position < length) {
        return hits[position]; // Return if the segment is hit or not
    }
    return false; // Position is out of range
}

// Get the count of hits on the ship
int Ship::getHitCount() const
{
    int count = 0;
    for (bool hit : hits) {
        if (hit) {
            count++;
        }
    }
    return count;
}

// Get the status of the ship
string Ship::getStatus() const
{
    string status = "Statek na pozycji (" + to_string(x) + ", " + to_string(y) + "): ";
    for (int i = 0; i < length; i++) {
        status += hits[i] ? "X" : "O"; // X - trafiony, O - nietrafiony
    }
    return status;
}
