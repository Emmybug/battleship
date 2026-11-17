// Handles computer controlled decisions

#include "computer.h"
#include <cstdlib> // For rand() and srand()

// Randomly place the computer's five ships
void placeComputerShips(Board& board, Ship fleet[5]) {

	for (int i = 0; i < 5; i++) {

		bool placed = false;

		// Keep trying until the ship is placed
		while (!placed) {

			//starting position
			int row = rand() % 10;
			int col = rand() % 10;

			char orientation;

			// Choose a random orientation
			if (rand() % 2 == 0) {
				orientation = 'H';
			}
			else {
				orientation = 'V';
			}

			// Let the Board class attempt placement
			placed = board.placeShip(
				row, col, fleet[i], orientation);
		}
	}

	cout << "\nComputer ships have been placed!\n";
}

// Function for the computer to attack
bool computerAttack(Board& trackingBoard,
	Board& playerBoard,
	Ship playerFleet[5]) {

	int row;
	int col;

	// Generate unused random coordinates
	do {
		row = rand() % 10;
		col = rand() % 10;

	} while (trackingBoard.getCell(row, col) != WATER);

	// Display the computer's chosen coordinate
	cout << "\nComputer attacks "
		<< char('A' + col)
		<< row + 1
		<< "!\n";

	// Save the original character before the attack
	char shipSymbol = playerBoard.getCell(row, col);

	// Attack the human player's ship board
	bool hit = playerBoard.receiveAttack(row, col);

	// Record the result on the computer's tracking board
	trackingBoard.markShot(row, col, hit);

	// Display result
	if (hit) {

		cout << RED
			<< "Computer has hit your ship!\n"
			<< RESET;

		// Determine whether the computer sank a ship
		reportSunkShip(
			playerFleet, shipSymbol, true);
	}
	else {

		cout << BLUE
			<< "Computer has missed!\n"
			<< RESET;
	}

	return hit;
}
