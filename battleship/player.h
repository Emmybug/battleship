#pragma once

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Text Color Codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string ORANGE = "\033[38;5;208m";
const string YELLOW = "\033[33m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string BLUE = "\033[34m";
const string PURPLE = "\033[35m";
const string PINK = "\033[38;5;212m";

// Define the structure for a ship
struct Ship {
	string name;
	int size;
	int hits;
	bool isSunk = false;
	string color;
};

// Function Prototypes
void initializeBoard(char board[10][10]);
void printBoard(char board[10][10], Ship fleet[]);
bool isValidPlacement(char board[10][10], int row, int col, int size, char orientation);
void boardSetup(char board[10][10], Ship fleet[]);
void attack(char trackBoard[10][10], char attackBoard[10][10]);
