//Starts the program, creates the boards, manages turns and determines the winners.

#include "Board.h" //Defines the Board class 
#include "computer.h" //Declares computer ship placement and attack functions
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time functions

int main() {

    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create the human player's boards
    Board playerShipBoard;
    Board playerTrackingBoard;

    // Create the computer's boards
    Board computerShipBoard;
    Board computerTrackingBoard;

    // Create the human player's fleet
    Ship playerFleet[5] = {
        { "Carrier", 5, 0, false, PURPLE },
        { "Battleship", 4, 0, false, YELLOW },
        { "Destroyer", 3, 0, false, GREEN },
        { "Submarine", 3, 0, false, PINK },
        { "Patrol Boat", 2, 0, false, ORANGE }
    };

    // Create the computer's fleet
    Ship computerFleet[5] = {
        { "Carrier", 5, 0, false, PURPLE },
        { "Battleship", 4, 0, false, YELLOW },
        { "Destroyer", 3, 0, false, GREEN },
        { "Submarine", 3, 0, false, PINK },
        { "Patrol Boat", 2, 0, false, ORANGE }
    };

    bool gameOver = false;
    bool playerTurn = true;

    // Welcome message
    cout << "Welcome to Battleship!\n";
    cout << "Let's set up your board!\n";

    // Set up the player's ships
    boardSetup(playerShipBoard, playerFleet);

    // Exit if input was closed during setup
    if (!cin) {
        return 0;
    }

    // Randomly place the computer's ships
    placeComputerShips(computerShipBoard, computerFleet);

    // DEBUG ONLY:
    // Uncomment these two lines to reveal enemy ships.
    // cout << "\n--- COMPUTER BOARD (DEBUG) ---\n";
    // computerShipBoard.print(computerFleet);

    // Main game loop
    while (!gameOver && cin) {

        // Human player's turn
        if (playerTurn) {

            cout << "\n---------- PLAYER TURN ----------\n";

            // Display tracking board
            cout << "\nYour tracking board:\n";
            playerTrackingBoard.print(playerFleet);

            // Display player's ship board
            cout << "\nYour ship board:\n";
            playerShipBoard.print(playerFleet);

            // Human attacks the computer
            bool hit = attack(
                playerTrackingBoard,
                computerShipBoard,
                computerFleet);

            // Stop if input was closed
            if (!cin) {
                break;
            }

            // Check whether computer has lost all ships
            if (!computerShipBoard.hasShipsRemaining()) {

                cout << GREEN
                    << "\nYou win! "
                    << "All enemy ships destroyed!\n"
                    << RESET;

                gameOver = true;
            }

            // If hit, human gets another turn
            else if (hit) {

                cout << GREEN
                    << "You hit a ship! Go again!\n"
                    << RESET;
            }

            // If miss, switch to computer turn
            else {

                cout << "You missed! Computer's turn.\n";

                playerTurn = false;
            }
        }

        // Computer's turn
        else {

            cout << "\n---------- COMPUTER TURN ----------\n";

            // Computer attacks the human
            bool hit = computerAttack(
                computerTrackingBoard,
                playerShipBoard,
                playerFleet);

            // Display player's board after the attack
            cout << "\nYour ship board:\n";
            playerShipBoard.print(playerFleet);

            // Check whether human has lost all ships
            if (!playerShipBoard.hasShipsRemaining()) {

                cout << RED
                    << "\nComputer wins! "
                    << "Your ships were destroyed!\n"
                    << RESET;

                gameOver = true;
            }

            // If hit, computer gets another turn
            else if (hit) {

                cout << RED
                    << "Computer hit! "
                    << "Computer goes again!\n"
                    << RESET;
            }

            // If miss, switch back to human turn
            else {

                cout << "Computer missed! Your turn.\n";

                playerTurn = true;
            }
        }
    }

    cout << "\nThanks for playing Battleship!\n";

    return 0;
}
