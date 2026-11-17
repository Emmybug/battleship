
#pragma once
#include "Board.h"

// Function Prototypes
bool computerAttack(Board& trackBoard,
    Board& playerBoard,
    Ship fleet[5]);

void placeComputerShips(Board& board, Ship fleet[5]);
