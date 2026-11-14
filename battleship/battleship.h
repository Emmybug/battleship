#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Text Color Codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";

// Define the structure for a ship
struct Ship {
	string name;
	int size;
	int hits;
	bool isSunk = false;
};

// Function Prototypes
void initializeBoard(char board[10][10]);
void printBoard(char board[10][10]);
bool isValidPlacement(char board[10][10], int row, int col, int size, char orientation);
void boardSetup(char board[10][10], Ship fleet[]);
