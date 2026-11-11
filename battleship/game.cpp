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
	cout << "  A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++) {
		cout << setw(2) << i + 1 << " ";
		for (int j = 0; j < 10; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	
	// Define the game boards for the player and computer
	char playerShipBoard[10][10], playerTrackingBoard[10][10], 
		computerShipBoard[10][10], computerTrackingBoard[10][10];

	initializeBoard(playerShipBoard);
	printBoard(playerShipBoard);

	return 0;

}