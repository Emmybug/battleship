
#include "player.h"
#include "Board.h"
#include <cctype>
#include <limits>

// Function to report when a ship is sunk
void reportSunkShip(Ship fleet[5], char shipSymbol,
    bool computerFired) {

    for (int i = 0; i < 5; i++) {
        if (fleet[i].name[0] == shipSymbol) {

            fleet[i].hits++;

            if (fleet[i].hits == fleet[i].size &&
                !fleet[i].isSunk) {

                fleet[i].isSunk = true;

                if (computerFired) {
                    cout << RED
                        << "Computer sank your "
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

// Function to set up the player's board with ships
void boardSetup(Board& board, Ship fleet[5]) {

    // Show the empty board before any ships are placed
    cout << "\nYour empty board:\n";
    board.print(fleet);

    for (int i = 0; i < 5; i++) {

        bool placed = false;

        // Keep asking until the current ship is placed
        while (!placed) {

            int row;
            string colInput;
            string orientationInput;

            cout << endl << "Place your " << fleet[i].name
                << YELLOW << " (size " << fleet[i].size
                << ")" << RESET << endl;

            // Get row and reprompt if invalid input
            cout << "Enter starting row"
                << YELLOW << " (1-10): " << RESET;

            while (!(cin >> row) || row < 1 || row > 10) {

                if (cin.eof()) {
                    return;
                }

                cout << RED << "Invalid input!!!\n"
                    << RESET
                    << "Please enter a number between 1 and 10: ";

                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');
            }

            row--; // Adjust for 0-based index

            // Get column and reprompt if invalid input
            cout << "\nEnter starting column"
                << YELLOW << " (A-J): " << RESET;

            while (true) {

                if (!(cin >> colInput)) {
                    return;
                }

                if (colInput.size() == 1 &&
                    toupper(colInput[0]) >= 'A' &&
                    toupper(colInput[0]) <= 'J') {
                    break;
                }

                cout << RED << "Invalid input!!!\n"
                    << RESET
                    << "Please enter a single letter "
                    << "between A and J: ";
            }

            int col = toupper(colInput[0]) - 'A';

            // Get the orientation
            cout << "\nEnter orientation"
                << YELLOW
                << " (H for horizontal, V for vertical): "
                << RESET;

            while (true) {

                if (!(cin >> orientationInput)) {
                    return;
                }

                if (orientationInput.size() == 1 &&
                    (toupper(orientationInput[0]) == 'H' ||
                        toupper(orientationInput[0]) == 'V')) {
                    break;
                }

                cout << RED
                    << "Invalid orientation!\n"
                    << RESET
                    << "Please enter H or V: ";
            }

            char orientation = orientationInput[0];

            // Check and place the ship using the Board class
            placed = board.placeShip(
                row, col, fleet[i], orientation);

            if (!placed) {
                cout << RED
                    << "Invalid placement!\n"
                    << RESET
                    << "Out of bounds or overlapping "
                    << "another ship. Try again.\n";
            }
        }

        cout << endl;
        board.print(fleet);
    }
}

// Function for the human player to attack
bool attack(Board& trackBoard, Board& attackBoard,
    Ship fleet[5]) {

    int shotRow;
    string shotColInput;

    bool shotFired = false;

    while (!shotFired) {

        cout << endl
            << "Time to attack!!\nEnter target row"
            << YELLOW << " (1-10): " << RESET;

        while (!(cin >> shotRow) ||
            shotRow < 1 || shotRow > 10) {

            if (cin.eof()) {
                return false;
            }

            cout << RED << "Invalid input!!!\n"
                << RESET
                << "Please enter a number between 1 and 10: ";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n');
        }

        shotRow--; // Adjust for 0-based index

        cout << "\nEnter target column"
            << YELLOW << " (A-J): " << RESET;

        while (true) {

            if (!(cin >> shotColInput)) {
                return false;
            }

            if (shotColInput.size() == 1 &&
                toupper(shotColInput[0]) >= 'A' &&
                toupper(shotColInput[0]) <= 'J') {
                break;
            }

            cout << RED << "Invalid input!!!\n"
                << RESET
                << "Please enter a single letter "
                << "between A and J: ";
        }

        int shotCol = toupper(shotColInput[0]) - 'A';

        // Check if this coordinate was already attacked
        if (!trackBoard.wasAttacked(shotRow, shotCol)) {

            // Remember the ship before it is marked as hit
            char shipSymbol =
                attackBoard.getCell(shotRow, shotCol);

            // Check if the player hit a ship
            bool hit =
                attackBoard.receiveAttack(shotRow, shotCol);

            // Update the player's tracking board
            trackBoard.markShot(shotRow, shotCol, hit);

            if (hit) {
                cout << YELLOW << "Hit!\n" << RESET;

                reportSunkShip(fleet, shipSymbol, false);
            }
            else {
                cout << BLUE << "Miss!\n" << RESET;
            }

            return hit;
        }
        else {
            cout << RED
                << "You already fired at that coordinate!"
                << RESET << " Try again.\n";
        }
    }

    return false;
}
