#include "player.h"

// Function to initialize the game board with water ('~')
void initializeBoard(char board[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = '~';
		}
	}
}

// Function to print the game board
void printBoard(char board[10][10], Ship fleet[5]) {
	cout << "   A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(2) << i + 1 << " ";
		for (int j = 0; j < 10; j++) {
			char cell = board[i][j];
			if (cell == '~') {
				cout << CYAN << cell << RESET << " ";
			}
			else if (cell == 'X') {
				cout << RED << cell << RESET << " ";
			}
			else if (cell == 'O') {
				cout << RESET << cell << " ";
			}
			else {
				string shipColor = RESET;
				for (int k = 0; k < 5; k++) {
					if (fleet[k].name[0] == cell) {
						shipColor = fleet[k].color;
						break;
					}
				}
				cout << shipColor << cell << RESET << " ";
			}
		}
		cout << endl;
	}
}

// Function to check if the ship placement is valid
bool isValidPlacement(char board[10][10], int row, int col, int size, char orientation) {
	if (toupper(orientation) != 'H' && toupper(orientation) != 'V') {
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

		// Get row and reprompt if invalid input
		cout << endl << "Place your " << fleet[i].name << YELLOW << " (size " << fleet[i].size << ")" << RESET << endl;
		cout << "Enter starting row" << YELLOW << " (1-10): " << RESET;
		while (!(cin >> row) || (row < 1 || row > 10)) {
			cout << RED << "Invalid input!!!\n" << RESET << "Please enter a number between 1 and 10: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
		row--; // Adjust for 0-based index

		// Get column and reprompt if invalid input
		cout << "\nEnter starting column" << YELLOW << " (A-J): " << RESET;
		cin >> colChar;
		while (toupper(colChar) < 'A' || toupper(colChar) > 'J') {
			cout << RED << "Invalid input!!!\n" << RESET << "Please enter a letter between A and J: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> colChar;
		}
		int col = toupper(colChar) - 'A'; // Convert column letter to index

		bool placed = false;
		while (!placed) {
			cout << "\nEnter orientation" << YELLOW << " (H for horizontal, V for vertical): " << RESET;
			cin >> orientation;

			if (isValidPlacement(board, row, col, fleet[i].size, orientation)) {
				char shipSymbol = fleet[i].name[0]; // 'C', 'B', 'D', 'S', or 'P'
				if (toupper(orientation) == 'H') {
					for (int j = 0; j < fleet[i].size; j++) {
						board[row][col + j] = shipSymbol; // Mark ship position
					}
				}
				else if (toupper(orientation) == 'V') {
					for (int j = 0; j < fleet[i].size; j++) {
						board[row + j][col] = shipSymbol; // Mark ship position
					}
				}
				placed = true;
			}
			else {
				cout << RED << "Invalid placement!\n" << RESET << "Out of bounds or overlapping another ship. Try again.";
			}
		}

		cout << endl;
		printBoard(board, fleet);
	}
}

void attack(char trackBoard[10][10], char attackBoard[10][10]) {
	int shotRow;
	char shotColChar;

	bool shotFired = false;
	while (!shotFired) {
		cout << endl << "Time to attack!!\nEnter target row" << YELLOW << " (1-10): " << RESET;
		while (!(cin >> shotRow) || (shotRow < 1 || shotRow > 10)) {
			cout << RED << "Invalid input!!!\n" << RESET << "Please enter a number between 1 and 10: ";
			cin.clear();
			cin.ignore(100, '\n');
		}
		shotRow--; //Adjust for 0-based index

		cout << "\nEnter target column" << YELLOW << " (A-J): " << RESET;
		cin >> shotColChar;
		while (toupper(shotColChar) < 'A' || toupper(shotColChar) > 'J') {
			cout << RED << "Invalid input!!!\n" << RESET << "Please enter a letter between A and J: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> shotColChar;
		}
		int shotCol = toupper(shotColChar) - 'A'; // Convert column letter to index

			
		if (trackBoard[shotRow][shotCol] == '~') {
			if (attackBoard[shotRow][shotCol] == 'S') {
				cout << YELLOW << "Hit!\n" << RESET;
				trackBoard[shotRow][shotCol] = 'X';
				attackBoard[shotRow][shotCol] = 'X';
			}
			else {
				cout << BLUE << "Miss!\n" << RESET;
				trackBoard[shotRow][shotCol] = 'O';
			}
			shotFired = true;
		}

		else {
			cout << RED << "You already fired at that coordinate!" << RESET << " Try again.\n";
		}
	}
}