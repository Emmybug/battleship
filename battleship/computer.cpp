
#include "computer.h"
#include <cstdlib>

// Function for the computer to attack the player's board
bool computerAttack(Board& trackBoard,
    Board& playerBoard,
    Ship fleet[5]) {

    int shotRow;
    int shotCol;

    // Generate random coordinates until an empty spot is found
    do {
        shotRow = rand() % 10;
        shotCol = rand() % 10;

    } while (trackBoard.wasAttacked(shotRow, shotCol));

    cout << "\nComputer attacks "
        << char('A' + shotCol)
        << shotRow + 1 << "!" << endl;

    // Remember which ship was at the target before the attack
    char shipSymbol =
        playerBoard.getCell(shotRow, shotCol);

    bool hit =
        playerBoard.receiveAttack(shotRow, shotCol);

    trackBoard.markShot(shotRow, shotCol, hit);

    // Check if the computer hit a ship
    if (hit) {

        cout << RED
            << "Computer has hit your ship!\n"
            << RESET;

        reportSunkShip(fleet, shipSymbol, true);

        return true;
    }
    else {

        cout << BLUE
            << "Computer has missed!\n"
            << RESET;

        return false;
    }
}

// Function to randomly place the computer's ships
void placeComputerShips(Board& board, Ship fleet[5]) {

    for (int i = 0; i < 5; i++) {

        bool placed = false;

        while (!placed) {

            int row = rand() % 10;
            int col = rand() % 10;

            char orientation;

            // Randomly choose horizontal or vertical
            if (rand() % 2 == 0) {
                orientation = 'H';
            }
            else {
                orientation = 'V';
            }

            // Check and place using the Board class
            placed = board.placeShip(
                row, col, fleet[i], orientation);
        }
    }

    cout << "\nComputer ships have been placed!\n";
}
