//Handle human player input and sinking announcements 

#include "player.h"
#include "Board.h"
#include <limits> //Input validation
using namespace std;

// Announce when a ship has been completely destroyed
void reportSunkShip(Ship fleet[5],
    char shipSymbol,
    bool computerFired) {

    for (int i = 0; i < 5; i++) {

        // Find the ship that was hit
        if (fleet[i].name[0] == shipSymbol) {

            // Increase the number of hits received
            fleet[i].hits++;

            // Check if all sections have been hit
            if (fleet[i].hits == fleet[i].size &&
                !fleet[i].isSunk) {

                fleet[i].isSunk = true;

                if (computerFired) {
                    cout << RED
                        << "The computer sank your "
                        << fleet[i].name << "!\n"
                        << RESET;
                }
                else {
                    cout << GREEN
                        << "You sank the enemy "
                        << fleet[i].name << "!\n"
                        << RESET;
                }
            }

            break;
        }
    }
}

// Function to set up the human player's ships

void boardSetup(Board& board, Ship fleet[5]) {

    board.print(fleet);

    for (int i = 0; i < 5; i++) {

        bool placed = false;

        // Keep asking until the current ship is placed
        while (!placed) {

            int row;
            string columnInput;
            char orientation;

            cout << "\nPlace your " << fleet[i].name
                << YELLOW
                << " (size " << fleet[i].size << ")"
                << RESET << endl;

            // Get starting row
            cout << "Enter starting row (1-10): ";

            while (!(cin >> row) ||
                row < 1 || row > 10) {

                cout << RED
                    << "Invalid row!\n"
                    << RESET
                    << "Enter 1-10: ";

                if (cin.eof()) {
                    return;
                }

                cin.clear();

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
            }

            // Convert to zero-based indexing
            row--;

            // Get starting column
            cout << "Enter starting column (A-J): ";
            cin >> columnInput;

            // Keep asking until the player enters exactly one valid letter
            while (columnInput.length() != 1 ||
                toupper(columnInput[0]) < 'A' ||
                toupper(columnInput[0]) > 'J') {

                cout << RED
                    << "Invalid column!\n"
                    << RESET
                    << "Enter a single letter from A to J: ";

                cin >> columnInput;
            }

            // Convert column letter to an array index
            int col = toupper(columnInput[0]) - 'A';


            // Get ship orientation
            cout << "Enter orientation (H or V): ";

            if (!(cin >> orientation)) {
                return;
            }

            // Validate orientation
            while (toupper(orientation) != 'H' &&
                toupper(orientation) != 'V') {

                cout << RED
                    << "Invalid orientation!\n"
                    << RESET
                    << "Enter H or V: ";

                if (!(cin >> orientation)) {
                    return;
                }
            }

            // Ask the Board object to place the ship
            placed = board.placeShip(
                row, col, fleet[i], orientation);

            // Inform the player if placement failed
            if (!placed) {
                cout << RED
                    << "Invalid placement: "
                    << "out of bounds or overlapping.\n"
                    << RESET
                    << "Choose another starting position.\n";
            }
        }

        // Display the board after each ship is placed
        cout << "\n";
        board.print(fleet);
    }
}

// Function for the human player to attack

bool attack(Board& trackingBoard,
    Board& opponentBoard,
    Ship opponentFleet[5]) {

    // Continue until the player chooses an unused coordinate
    while (true) {

        int row;
        char columnLetter;

        cout << "\nTime to attack!\n";

        // Get target row
        cout << "Enter target row (1-10): ";

        while (!(cin >> row) ||
            row < 1 || row > 10) {

            cout << RED
                << "Invalid row!\n"
                << RESET
                << "Enter 1-10: ";

            if (cin.eof()) {
                return false;
            }

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n');
        }

        // Convert to zero-based indexing
        row--;

        // Get target column
        cout << "Enter target column (A-J): ";

        if (!(cin >> columnLetter)) {
            return false;
        }

        // Validate column
        while (toupper(columnLetter) < 'A' ||
            toupper(columnLetter) > 'J') {

            cout << RED
                << "Invalid column!\n"
                << RESET
                << "Enter A-J: ";

            if (!(cin >> columnLetter)) {
                return false;
            }
        }

        // Convert the letter to an array index
        int col = toupper(columnLetter) - 'A';

        // Check whether this position was already attacked
        if (trackingBoard.wasAttacked(row, col)) {

            cout << RED
                << "You already fired at that coordinate!"
                << " Try again.\n"
                << RESET;

            continue;
        }

        // Remember what was at the target position
        char shipSymbol =
            opponentBoard.getCell(row, col);

        // Attack the opponent's ship board
        bool hit =
            opponentBoard.receiveAttack(row, col);

        // Record the result on the tracking board
        trackingBoard.markShot(row, col, hit);

        // Display result
        if (hit) {

            cout << YELLOW
                << "Hit!\n"
                << RESET;

            // Check whether this hit sank a ship
            reportSunkShip(
                opponentFleet, shipSymbol, false);
        }
        else {

            cout << BLUE
                << "Miss!\n"
                << RESET;
        }

        // Return result to main.cpp
        return hit;
    }
}
