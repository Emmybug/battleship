//Declares the computers functions
//Implementation are in computer.cpp
#pragma once
#include "Board.h"

// Randomly place the computer's five ships
void placeComputerShips(Board& board, Ship fleet[5]);

// Computer attacks the human player
bool computerAttack(Board& trackingBoard,
    Board& playerBoard,
    Ship playerFleet[5]);
