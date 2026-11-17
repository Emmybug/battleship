
#include "Board.h"
#include "computer.h"
#include <cstdlib>
#include <ctime>

int main() {

    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Define the game boards for the player and computer
    Board playerShipBoard;
    Board playerTrackingBoard;
    Board computerShipBoard;
    Board computerTrackingBoard;

    bool gameOver = false;
    bool playerTurn = true;

    // Define the fleet of ships for the player
    Ship fleet[5] = {
        {"Carrier", 5, 0, false, PURPLE},
        {"Battleship", 4, 0, false, YELLOW},
        {"Destroyer", 3, 0, false, GREEN},
        {"Submarine", 3, 0, false, PINK},
        {"Patrol Boat", 2, 0, false, ORANGE}
    };

    // Define a separate fleet for the computer
    Ship computerFleet[5] = {
        {"Carrier", 5, 0, false, PURPLE},
        {"Battleship", 4, 0, false, YELLOW},
        {"Destroyer", 3, 0, false, GREEN},
        {"Submarine", 3, 0, false, PINK},
        {"Patrol Boat", 2, 0, false, ORANGE}
    };

    // Game setup phase
    cout << "Welcome to Battleship! "
        << "Let's set up your board!"
        << endl << endl;

    boardSetup(playerShipBoard, fleet);

    if (!cin) {
        return 0;
    }

    placeComputerShips(computerShipBoard, computerFleet);

    // Uncomment to see the computer's ships during testing:
    // cout << "\nCOMPUTER BOARD (DEBUG):\n";
    // computerShipBoard.print(computerFleet);

    // Main game loop
    while (!gameOver && cin) {

        if (playerTurn) {

            cout << "\n---------- PLAYER TURN ----------\n";

            cout << "\nYour tracking board:\n";
            playerTrackingBoard.print(fleet);

            cout << "\nYour ship board:\n";
            playerShipBoard.print(fleet);

            // Receive player's shot input
            bool hit = attack(
                playerTrackingBoard,
                computerShipBoard,
                computerFleet);

            if (!cin) {
                break;
            }

            // Check if all computer ships are destroyed
            if (!computerShipBoard.hasShipsRemaining()) {

                cout << GREEN
                    << "\nYou win! All enemy ships have been destroyed!\n"
                    << RESET;

                gameOver = true;
            }
            else if (hit) {

                cout << GREEN
                    << "You hit a ship! Go again!\n"
                    << RESET;
            }
            else {

                cout << "You missed! Computer's turn.\n";
                playerTurn = false;
            }
        }
        else {

            cout << "\n---------- COMPUTER TURN ----------\n";

            // Computer attacks the player's board
            bool hit = computerAttack(
                computerTrackingBoard,
                playerShipBoard,
                fleet);

            cout << "\nYour ship board:\n";
            playerShipBoard.print(fleet);

            // Check if all player ships are destroyed
            if (!playerShipBoard.hasShipsRemaining()) {

                cout << RED
                    << "\nComputer wins! "
                    << "Your ships were destroyed!\n"
                    << RESET;

                gameOver = true;
            }
            else if (hit) {

                cout << RED
                    << "Computer hit! Computer goes again!\n"
                    << RESET;
            }
            else {

                cout << "Computer missed! Your turn.\n";
                playerTurn = true;
            }
        }
    }

    cout << "\nThanks for playing Battleship!\n";

    return 0;
}
