#include "battleship.h"

int main() {
	
	// Define the game boards for the player and computer
	char playerShipBoard[10][10], playerTrackingBoard[10][10], 
		computerShipBoard[10][10], computerTrackingBoard[10][10];

	bool gameOver = false;

	// Define the fleet of ships for the player
	Ship fleet[5] = {
		{ "Carrier", 5, 0, false},
		{ "Battleship", 4, 0, false},
		{ "Destroyer", 3, 0, false},
		{ "Submarine", 3, 0, false},
		{ "Patrol Boat", 2, 0, false}
	};

	initializeBoard(playerShipBoard);
	initializeBoard(playerTrackingBoard);
	initializeBoard(computerShipBoard);
	initializeBoard(computerTrackingBoard);

	// Game setup phase
	cout << "Welcome to Battleship! Let's set up your board!" << endl << endl;
	printBoard(playerShipBoard);
	boardSetup(playerShipBoard, fleet);

	while (!gameOver) {
		cout << "\n- - - - - - - - - - - - - - - - - -\n";
		cout << "Your tracking board:\n";
		printBoard(playerTrackingBoard);

		cout << "\nYour ship board:\n";
		printBoard(playerShipBoard);

		// Receiving player's shot input
		int shotRow;
		char shotColChar;
		cout << endl << "Time to attack!!\nEnter target row (1-10): ";
		cin >> shotRow;
		cout << "Enter target column (A-J): ";
		cin >> shotColChar;

		shotRow--; // Adjust for 0-based index
		int shotCol = toupper(shotColChar) - 'A'; // Convert column letter to index

		if (shotRow >= 0 && shotRow < 10 && shotCol >= 0 && shotCol < 10) {
			if (playerTrackingBoard[shotRow][shotCol] = '~') {
				if (computerShipBoard[shotRow][shotCol] == 'S') {
					cout << "Hit!\n";
					playerTrackingBoard[shotRow][shotCol] = 'X';
					computerShipBoard[shotRow][shotCol] = 'X';
				}
				else {
					cout << "Miss!\n";
					playerTrackingBoard[shotRow][shotCol] = 'O';
				}
			}

			else {
				cout << "You already fired at that coordinate! Try again.\n";
			}
		}
		else {
			cout << "Coordinates out of bounds! Try again!";
		}

		cout << "End? (Enter 1 to quit): ";
		int quitCheck;
		cin >> quitCheck;
		if (quitCheck == 1) {
			gameOver = true;
		}
	}

	return 0;

}