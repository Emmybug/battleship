#include "battleship.h"

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
			if (board[i][j] == '~') {
				cout << CYAN << board[i][j] << RESET << " ";
			}
			else if (board[i][j] == 'S') {
				// Optional: You can color your ships green or leave them default!
				cout << GREEN << board[i][j] << RESET << " ";
			}
			else if (board[i][j] == 'X') {
				cout << RED << board[i][j] << RESET << " ";
			}
			else {
				cout << board[i][j] << " ";
			}
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
		char colChar;
		char orientation;
		cout << endl << "Place your " << fleet[i].name << " (size " << fleet[i].size << ")" << endl;
		cout << "Enter starting row (1-10): ";
		cin >> row;
		cout << "Enter starting column (A-J): ";
		cin >> colChar;
		cout << "Enter orientation (H for horizontal, V for vertical): ";
		cin >> orientation;
		row--; // Adjust for 0-based index
		int col = toupper(colChar) - 'A'; // Convert column letter to index

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