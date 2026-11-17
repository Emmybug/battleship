/*Defines what a board object contains and what it is able to do.*/

#pragma once
#include "player.h"

// A board owns a 10x10 grid and the operations on that grid.
class Board {
private:
    char grid[10][10];

public:
    Board();

    void initialize();

    void print(Ship fleet[5]) const;

    bool isValidPlacement(int row, int col,
        int size, char orientation) const;

    bool placeShip(int row, int col,
        Ship ship, char orientation);

    bool wasAttacked(int row, int col) const;

    bool receiveAttack(int row, int col);

    void markShot(int row, int col, bool hit);

    char getCell(int row, int col) const;

    bool hasShipsRemaining() const;
};
