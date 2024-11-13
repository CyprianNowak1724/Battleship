#include "Player.h"
#include <iostream>
#include "Board.h"

using namespace std;

Player::Player(const string& name) : name(name), ships() {
    ownBoard = new Board;       // Player's board (where ships are placed)
    shotBoard = new Board;      // Shot board (attack results)
    // Initializing ships
    ships.push_back(Ship(0, 0, 1, true));  // 1-mast ship
    ships.push_back(Ship(1, 0, 1, true));  // 1-mast ship
    ships.push_back(Ship(2, 0, 1, true));  // 1-mast ship
    ships.push_back(Ship(3, 0, 1, true));  // 1-mast ship
    ships.push_back(Ship(0, 1, 2, true));  // 2-mast ship
    ships.push_back(Ship(0, 2, 2, true));  // 2-mast ship
    ships.push_back(Ship(0, 3, 2, true));  // 2-mast ship
    ships.push_back(Ship(0, 4, 3, true));  // 3-mast ship
    ships.push_back(Ship(0, 5, 3, true));  // 3-mast ship
    ships.push_back(Ship(0, 6, 4, true));  // 4-mast ship
}



void Player::placeShips(Player& opponent) {
    cout << "Umiesc statki dla " << name << endl;

    // Defining the number of ships
    const int oneMastCount = 4;
    const int twoMastCount = 3;
    const int threeMastCount = 2;
    const int fourMastCount = 1;

    // Placing ships
    for (int i = 0; i < oneMastCount; i++) {
        cout << "Umiesc 1-masztowiec " << endl;
        placeShip(1, opponent);
    }
    for (int i = 0; i < twoMastCount; i++) {
        cout << "Umiesc 2-masztowiec " << endl;
        placeShip(2, opponent);
    }
    for (int i = 0; i < threeMastCount; i++) {
        cout << "Umiesc 3-masztowiec " << endl;
        placeShip(3, opponent);
    }
    for (int i = 0; i < fourMastCount; i++) {
        cout << "Umiesc 4-masztowiec " << endl;
        placeShip(4, opponent);
    }
}


void Player::displayBoardWithCoordinates() const {
    cout << "\n--- " << name << " - Twoja plansza ---\n";
    ownBoard->display();

    cout << "\n--- " << name << " - Plansza strzalow na przeciwnika ---\n";
    shotBoard->display(); 
}

void Player::updateShotBoard(int x, int y, bool hit) {
    shotBoard->setCell(x, y, hit ? SHOOT_FIELD : MISS_FIELD);  // SHOOT_FIELD for a hit, MISS_FIELD for a miss
}

void Player::placeShip(int length, Player& opponent) {
    char direction = 'H';  // Default direction for a single-mast ship
    int x, y;

    if (length == 1) {
    } else {
        // Asking for the direction for ships longer than 1 mast
        while (true) {
            cout << "Podaj kierunek (H-poziomo/V-pionowo): ";
            cin >> direction;
            direction = toupper(direction);  // Convert to uppercase

            // Direction validation
            if (direction != 'H' && direction != 'V') {
                cout << "Kierunek musi byc H (poziomo) lub V (pionowo). Sprobuj ponownie." << endl;
                continue;
            }
            break;  // Exit the loop if the direction is valid
        }
    }

    while (true) {
        string input;
        cout << "Podaj wspolrzedne (np. A5): ";
        cin >> input;

        // Coordinate validation
        if (input.length() < 2 || input.length() > 3) {
            cout << "Niepoprawny format wspolrzednych. Sprobuj ponownie." << endl;
            continue;  // Return to the beginning of the loop
        }

        // Convert coordinates
        x = toupper(input[0]) - 'A';  // Convert letter to index
        if(input[1] == '0')
        {
            cout << "Nie mozesz zaznaczyc tego pola!" << endl;
            continue;
        }

        if(input[1] < '0' || input[1] > '9')
        {
            cout << "To nie jest liczba!" << endl;
            continue;
        }

        if(input.size() == 3)
        {
            if(input[2] < '0' || input[1] > '9')
            {
                cout << "To nie jest liczba!" << endl;
                continue;
            }
        }

        y = stoi(input.substr(1)) - 1;  // Convert number to index

        // Check if the coordinates are within the correct range
        if (x < 0 || x >= Board::BOARD_SIZE || y < 0 || y >= Board::BOARD_SIZE) {
            cout << "Wspolrzedne musza byc w zakresie A1 do J10. Sprobuj ponownie." << endl;
            continue;  // Return to the beginning of the loop
        }

        // Check if the ship can be placed
        bool canPlace = ownBoard->canPlaceShip(x, y, length, direction == 'H');
        if (canPlace) {
            ownBoard->addShip(x, y, length, direction == 'H');
            cout << "Statek ustawiony pomyslnie!" << endl;
            displayBoardWithCoordinates();  // Display both boards
            break;  // Exit the loop after successfully placing the ship
        } else {
            cout << "Nie mozna umiescic statku w tej lokalizacji! Sprobuj ponownie." << endl;
            displayBoardWithCoordinates();  // Display both boards after an unsuccessful attempt
        }
    }
}

Board& Player::getOwnBoard() {
    return *ownBoard;
}


bool Player::attack(int x, int y, Player& opponent) {
    // Perform the shot on the opponent's board (ownBoard of opponent)
    char hit = opponent.ownBoard->shoot(x, y);
    

    // Update the target board based on the shot result
    shotBoard->setCell(x, y, hit);  // SHOOT_FIELD for a hit, MISS_FIELD for a miss

    return hit == SHOOT_FIELD;  // Return 'hit' - true for a hit, false for a miss
}

bool Player::takeTurn(Player& opponent) {
    int x, y;
    bool validShot = false;
    bool hit = false;

    while (!validShot) {
        string input;
        cout << getName() << ", podaj wspolrzedne ataku (np. A5): ";
        cin >> input;

        // Check input length
        if (input.length() < 2 || input.length() > 3) {
            cout << "Niepoprawny format wspolrzednych! Uzyj formatu A1 do J10." << endl;
            continue;
        }

        // Convert the first character to a column index (A -> 0, B -> 1, etc.)
        x = toupper(input[0]) - 'A';

        // Check if the remaining characters are digits, i.e., a number
        string rowPart = input.substr(1);
        bool isNumber = true;
        for (unsigned int i = 0; i < rowPart.length(); i++) 
        {
            if (!isdigit(rowPart[i])) 
            {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "Niepoprawny format liczby w wierszu! Uzyj cyfr od 1 do 10." << endl;
            continue;
        }

        // Convert the row number and adjust it to a zero-based index
        y = stoi(rowPart) - 1;

        // Check if the coordinates are within range
        if (x < 0 || x >= Board::BOARD_SIZE || y < 0 || y >= Board::BOARD_SIZE) {
            cout << "Wspolrzedne musza byc w zakresie A1 do J10. Sprobuj ponownie." << endl;
            continue;
        }

        char currentCell = shotBoard->getCell(x, y);
        if (currentCell == SHOOT_FIELD || currentCell == MISS_FIELD) {
            cout << "Juz strzelano w to miejsce! Wybierz inne wspolrzedne." << endl;
            continue;  // The shot has already been taken, player must choose another cell
        }

        // Perform the shot and mark it as valid
        hit = attack(x, y, opponent);
        validShot = true;
    }

    if (hit) {
        // If the ship is sunk, mark it with "O" on the opponent's board
        shotBoard->markSunkShipsWithO(opponent.ownBoard);
    }

    return hit;  // Return true if hit, false if miss
}

Player::~Player()
{
    delete ownBoard;      
    delete shotBoard;  
}

bool Player::allShipsSunk() const {
    return ownBoard->allShipsSunk();  // Check if all ships have been sunk
}

string Player::getName() const
{
    return name; 
}
