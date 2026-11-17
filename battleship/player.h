/* Job is to define the shared info and declare the huiman player functions*/
#pragma once

#include <iostream> //Input and output
#include <iomanip> //Output formatting
#include <string> //Working with text

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

/*
no longer use these as instead of using the arrays we use board playerShipBoard; whihc acts
as an object. so initialize board became board::initialize() and print board became board::print() etc.
which are in board.h or player.h.

The & means we're passing the actual Board object by reference,
so changes made inside boardSetup() affect the original board.

Function Prototypes
void initializeBoard(char board[10][10]);
void printBoard(char board[10][10], Ship fleet[]);
bool isValidPlacement(char board[10][10], int row, int col, int size, char orientation);
void boardSetup(char board[10][10], Ship fleet[]);
bool attack(char trackBoard[10][10], char attackBoard[10][10]);
bool hasShipsRemaining(char board[10][10]);*/

// Board character constants
const char WATER = '~';
const char HIT = 'X';
const char MISS = 'O';

// Structure for an individual ship
struct Ship {
    string name;
    int size;
    int hits;
    bool isSunk;
    string color;
};

// Forward declaration of the Board class
class Board;

// Function Prototypes
// Allow the human player to place ships
void boardSetup(Board& board, Ship fleet[5]);

// Allow the human player to attack
bool attack(Board& trackingBoard,
    Board& opponentBoard,
    Ship opponentFleet[5]);

// Check whether a ship has sunk
void reportSunkShip(Ship fleet[5],
    char shipSymbol,
    bool computerFired);
