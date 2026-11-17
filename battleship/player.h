
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

// Board character constants
const char WATER = '~';
const char HIT = 'X';
const char MISS = 'O';

// Define the structure for a ship
struct Ship {
    string name;
    int size;
    int hits;
    bool isSunk = false;
    string color;
};

// A Board is defined in Board.h
class Board;

// Function Prototypes
void boardSetup(Board& board, Ship fleet[5]);

bool attack(Board& trackBoard, Board& attackBoard,
    Ship fleet[5]);

void reportSunkShip(Ship fleet[5], char shipSymbol,
    bool computerFired);
