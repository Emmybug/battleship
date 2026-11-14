#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Define the structure for a ship
struct Ship {
	string name;
	int size;
	int hits;
	bool isSunk = false;
};

// Function to initialize the game board with water ('~')
void initializeBoard(char board[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = '~';
		}
	}
}

// Function to print the game board
void printBoard(char board[10][10]) {
	cout << "   A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(2) << i + 1 << " ";
		for (int j = 0; j < 10; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

// Function to check if the ship placement is valid
bool isValidPlacement(char board[10][10], int row, int col, int size, char orientation) {
	if (row < 0 || row >= 10 || col < 0 || col >= 10) {
		return false;
	}

	if (toupper(orientation) == 'H') {
		for (int j = 0; j < size; j++) {
			if (col + j >= 10 || board[row][col + j] == 'S') {
				return false;
			}
		}
	}
	else if (toupper(orientation) == 'V') {
		for (int j = 0; j < size; j++) {
			if (row + j >= 10 || board[row + j][col] == 'S') {
				return false;
			}
		}
	}

	return true;
}

// Function to set up the player's board with ships
void boardSetup(char board[10][10], Ship fleet[]) {
	for (int i = 0; i < 5; i++) {
		int row;
		char col, orientation;
		cout << endl << "Place your " << fleet[i].name << " (size " << fleet[i].size << ")" << endl;
		cout << "Enter starting row (1-10): ";
		cin >> row;
		cout << "Enter starting column (A-J): ";
		cin >> col;
		cout << "Enter orientation (H for horizontal, V for vertical): ";
		cin >> orientation;
		row--; // Adjust for 0-based index
		col = toupper(col) - 'A'; // Convert column letter to index

		if (isValidPlacement(board, row, col, fleet[i].size, orientation)) {
			if (toupper(orientation) == 'H') {
				for (int j = 0; j < fleet[i].size; j++) {
					board[row][col + j] = 'S'; // Mark ship position
				}
			}
			else if (toupper(orientation) == 'V') {
				for (int j = 0; j < fleet[i].size; j++) {
					board[row + j][col] = 'S'; // Mark ship position
				}
			}
		}
		else {
			cout << "Invalid placement! Out of bounds or overlapping another ship. Try again.\n\n";
			i--; // Repeat the current ship placement
		}
		cout << endl;
		printBoard(board);
	}
}

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
		char shotCol;
		cout << endl << "Time to attack!!\nEnter target row (1-10): ";
		cin >> shotRow;
		cout << "Enter target column (A-J): ";
		cin >> shotCol;

		shotRow--; // Adjust for 0-based index
		shotCol = toupper(shotCol) - 'A'; // Convert column letter to index

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