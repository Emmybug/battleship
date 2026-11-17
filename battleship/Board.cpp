//Contains the actual implementation of the Board class functions
//Functions in board.h are implemented here in board.cpp

#include "Board.h"

// Constructor - initialize the board when created, runs auto when an object is created
Board::Board() {
    initialize();
}

// Fill the board with water
void Board::initialize() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = WATER;
        }
    }
}

// Display the board with colors, uses nested for loops. Out=row, in=column
//fleet is the paramter to determine the color of the ships
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
                // Find the color for the ship
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

// Check whether a ship placement is valid
bool Board::isValidPlacement(int row, int col,
    int size, char orientation) const {

    orientation = static_cast<char>(toupper(orientation));

    // Check orientation
    if (orientation != 'H' && orientation != 'V') {
        return false;
    }

    // Check starting position and ship size
    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10 || size <= 0) {
        return false;
    }

    // Check horizontal placement
    if (orientation == 'H') {
        for (int j = 0; j < size; j++) {

            if (col + j >= 10 ||
                grid[row][col + j] != WATER) {
                return false;
            }
        }
    }

    // Check vertical placement
    else {
        for (int j = 0; j < size; j++) {

            if (row + j >= 10 ||
                grid[row + j][col] != WATER) {
                return false;
            }
        }
    }

    return true;
}

// Place a ship on the board
bool Board::placeShip(int row, int col,
    Ship ship, char orientation) {

    // Reject invalid placements
    if (!isValidPlacement(row, col,
        ship.size, orientation)) {
        return false;
    }

    char shipSymbol = ship.name[0];

    orientation = static_cast<char>(toupper(orientation));

    // Place ship sections
    for (int j = 0; j < ship.size; j++) {

        if (orientation == 'H') {
            grid[row][col + j] = shipSymbol;
        }
        else {
            grid[row + j][col] = shipSymbol;
        }
    }

    return true;
}

// Check whether a position was already attacked
bool Board::wasAttacked(int row, int col) const {

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10) {
        return false;
    }

    return grid[row][col] == HIT ||
        grid[row][col] == MISS;
}

// Receive an attack and return true for a hit
bool Board::receiveAttack(int row, int col) {

    // Reject invalid or previously attacked positions
    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10 ||
        wasAttacked(row, col)) {
        return false;
    }

    // Determine whether a ship was hit
    bool hit = grid[row][col] != WATER;

    // Record hit or miss
    if (hit) {
        grid[row][col] = HIT;
    }
    else {
        grid[row][col] = MISS;
    }

    return hit;
}

// Record the result on a tracking board
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

// Return the character stored at a position, remembers which ship was hit before attacked
char Board::getCell(int row, int col) const {

    if (row < 0 || row >= 10 ||
        col < 0 || col >= 10) {
        return '?';
    }

    return grid[row][col];
}

// Check whether any undamaged ships remain
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
