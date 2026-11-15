#include "player.h"
#include "computer.h"

int main() {
	
	// Define the game boards for the player and computer
	char playerShipBoard[10][10], playerTrackingBoard[10][10], 
		computerShipBoard[10][10], computerTrackingBoard[10][10];

	bool gameOver = false;

	// Define the fleet of ships for the player
	Ship fleet[5] = {
		{ "Carrier", 5, 0, false, PURPLE},
		{ "Battleship", 4, 0, false, YELLOW},
		{ "Destroyer", 3, 0, false, GREEN},
		{ "Submarine", 3, 0, false, PINK},
		{ "Patrol Boat", 2, 0, false, ORANGE}
	};

	initializeBoard(playerShipBoard);
	initializeBoard(playerTrackingBoard);
	initializeBoard(computerShipBoard);
	initializeBoard(computerTrackingBoard);

	// Game setup phase
	cout << "Welcome to Battleship! Let's set up your board!" << endl << endl;
	printBoard(playerShipBoard, fleet);
	boardSetup(playerShipBoard, fleet);

	while (!gameOver) {
		cout << "\n- - - - - - - - - - - - - - - - - -\n";
		cout << "Your tracking board:\n";
		printBoard(playerTrackingBoard, fleet);

		cout << "\nYour ship board:\n";
		printBoard(playerShipBoard, fleet);

		// Receiving player's shot input
		attack(playerTrackingBoard, computerShipBoard);

		cout << "End? (Enter 1 to quit): ";
		int quitCheck;
		cin >> quitCheck;
		if (quitCheck == 1) {
			gameOver = true;
		}
	}

	return 0;

}