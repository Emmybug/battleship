
#include "Board.h"
#include <cctype>

// Constructor - initialize the board when it is created
Board::Board() {
    initialize();
}

// Function to initialize the game board with water ('~')
void Board::initialize() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = WATER;
        }
    }
}

// Function to print the game board
void Board::print(Ship fleet[5]) const {
    cout << "   A B C D E F G H I J" << endl;

    for (int i = 0; i < 10; i++) {
        cout << setw(2) << i + 1 << " ";

        for (int j = 0; j < 10; j++) {
            char cell = grid[i][j];

            if (cell == WATER) {
                cout << CYAN << cell << RESET << " ";
            }
            else if (cell == HIT) {
                cout << RED << cell << RESET << " ";
            }
            else if (cell == MISS) {
                cout << RESET << cell << " ";
            }
            else {
                string shipColor = RESET;

                for (int k = 0; k < 5; k++) {
                    if (fleet[k].name[0] == cell) {
                        shipColor = fleet[k].color;
                        break;
                    }
                }

                cout << shipColor << cell << RESET << " ";
            }
        }

        cout << endl;
    }
}

// Function to check if the ship placement is valid
bool Board::isValidPlacement(int row, int col,
    int size, char orientation) const {

    orientation = static_cast<char>(toupper(orientation));

    if (orientation != 'H' && orientation != 'V') {
        return false;
    }

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10 || size <= 0) {
        return false;
    }

    if (orientation == 'H') {
        for (int j = 0; j < size; j++) {
            if (col + j >= 10 ||
                grid[row][col + j] != WATER) {
                return false;
            }
        }
    }
    else if (orientation == 'V') {
        for (int j = 0; j < size; j++) {
            if (row + j >= 10 ||
                grid[row + j][col] != WATER) {
                return false;
            }
        }
    }

    return true;
}

// Function to place a ship after checking its position
bool Board::placeShip(int row, int col,
    Ship ship, char orientation) {

    if (!isValidPlacement(row, col,
        ship.size, orientation)) {
        return false;
    }

    char shipSymbol = ship.name[0];

    if (toupper(orientation) == 'H') {
        for (int j = 0; j < ship.size; j++) {
            grid[row][col + j] = shipSymbol;
        }
    }
    else {
        for (int j = 0; j < ship.size; j++) {
            grid[row + j][col] = shipSymbol;
        }
    }

    return true;
}

// Function to check whether a location was already attacked
bool Board::wasAttacked(int row, int col) const {

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10) {
        return false;
    }

    return grid[row][col] == HIT ||
        grid[row][col] == MISS;
}

// Function to receive an attack
bool Board::receiveAttack(int row, int col) {

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10 ||
        wasAttacked(row, col)) {
        return false;
    }

    bool hit = grid[row][col] != WATER;

    if (hit) {
        grid[row][col] = HIT;
    }
    else {
        grid[row][col] = MISS;
    }

    return hit;
}

// Function to record an attack on a tracking board
void Board::markShot(int row, int col, bool hit) {

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10) {
        return;
    }

    if (hit) {
        grid[row][col] = HIT;
    }
    else {
        grid[row][col] = MISS;
    }
}

// Function to return a board character
char Board::getCell(int row, int col) const {

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10) {
        return '?';
    }

    return grid[row][col];
}

// Function to check if any ships are left
bool Board::hasShipsRemaining() const {

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            if (grid[i][j] != WATER &&
                grid[i][j] != HIT &&
                grid[i][j] != MISS) {
                return true;
            }
        }
    }

    return false;
}
