#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;

/* functions */
void setup();
bool validity(int, int);
bool checkWin(int, int);
void printBoard();
void nextPlayer();
bool gameOver();

/* global variables */
int BOARDROWS = 3;
int BOARDCOLS = 3;
int COUNT = 3;
string playerOne = "X", playerTwo = "O";
vector<vector<string>> board;
string CURRENTPLAYER;

int main()
{
	int rowGuessed;
	int colGuessed;
	string keepPlaying;

	/* Game loop */
	while (true) {
		/* New game*/
		setup();
		while (!gameOver()) {
			printBoard();
			cout << "Player: " + CURRENTPLAYER << endl;
			cout << "Enter the row: " << endl;
			while (!(cin >> rowGuessed)) {
				cin.clear();
				cin.ignore();
				cout << "Please enter an integer" << endl;
			}
			cout << "Enter the column: " << endl;
			while (!(cin >> colGuessed)) {
				cin.clear();
				cin.ignore();
				cout << "Please enter an integer" << endl;
			}
			while (!validity(rowGuessed - 1, colGuessed - 1)) {
				cout << "Invalid, please try again" << endl;
				cout << "Enter the row: " << endl;
				while (!(cin >> rowGuessed)) {
					cin.clear();
					cin.ignore();
					cout << "Please enter an integer" << endl;
				}
				cout << "Enter the column: " << endl;
				while (!(cin >> colGuessed)) {
					cin.clear();
					cin.ignore();
					cout << "Please enter an integer" << endl;
				}
			}
			if (checkWin(rowGuessed - 1, colGuessed - 1)) {
				cout << "========\tPlayer: " + CURRENTPLAYER + " has won\t========" << endl;
				printBoard();
				break;
			}
			nextPlayer();
		}
		cout << "Play again? (y/n)" << endl;
		cin >> keepPlaying;
		while (keepPlaying != "y" && keepPlaying != "n") {
			cout << "Please enter y or n" << endl;
			cin.clear();
			cin.ignore();
			cin >> keepPlaying;
		}
		if (keepPlaying == "n") {
			return 0;
		}
	}
}

void setup() {
	CURRENTPLAYER = playerOne;
	cout << "Enter the board's row size : " << endl;
	while (!(cin >> BOARDROWS)) {
		cin.clear();
		cin.ignore();
		cout << "Please enter an integer" << endl;
	}
	cout << "Enter the board's column size : " << endl;
	while (!(cin >> BOARDCOLS)) {
		cin.clear();
		cin.ignore();
		cout << "Please enter an integer" << endl;
	}
	cout << "How many in a row to win ? : " << endl;
	while (!(cin >> COUNT)) {
		cin.clear();
		cin.ignore();
		cout << "Please enter an integer" << endl;
	}
	board.clear();
	board.resize(BOARDROWS, vector<string>(BOARDCOLS));
	for (int i = 0; i < BOARDROWS; i++) {
		for (int j = 0; j < BOARDCOLS; j++) {
			board[i][j] = "|_|";
		}
	}
	cout << endl;
}

bool validity(int row, int col) {
	if (row >= BOARDROWS || col >= BOARDCOLS) {
		return false;
	}
	if (board[row][col] == "|_|") {
		board[row][col] = "|" + CURRENTPLAYER + "|";
		return true;
	}
	return false;
}

/*
	Checks if current move
	is a win.
*/
bool checkWin(int row, int col) {
	int counter = 0;
	/* check row */
	for (int i = 0; i < BOARDCOLS; i++) {
		if (board[row][i].substr(1, 1) == CURRENTPLAYER) {
			counter++;
		}
		else {
			counter = 0;
		}
		if (counter == COUNT) {
			return true;
		}
	}
	counter = 0;
	/* check column */
	for (int i = 0; i < BOARDROWS; i++) {
		if (board[i][col].substr(1, 1) == CURRENTPLAYER) {
			counter++;
		}
		else {
			counter = 0;
		}
		if (counter == COUNT) {
			return true;
		}
	}

	/* check backward diaganol */
	counter = 0;
	int tempRow = row, tempCol = col;
	/* backtrack diaganolly */
	while ((tempRow >= 0 && tempCol >= 0) &&
		(board[tempRow][tempCol].substr(1, 1) == CURRENTPLAYER)) {
		tempRow--;
		tempCol--;
		counter++;
	}
	/* forward track */
	tempRow = row + 1, tempCol = col + 1;
	while ((tempRow < BOARDROWS && tempCol < BOARDCOLS) &&
		(board[tempRow][tempCol].substr(1, 1) == CURRENTPLAYER)) {
		tempRow++;
		tempCol++;
		counter++;
	}
	if (counter >= COUNT) {
		return true;
	}

	/* check forward diaganol */
	counter = 0;
	tempRow = row, tempCol = col;
	/* backtrack diaganolly */
	while ((tempRow < BOARDROWS && tempCol >= 0) &&
		(board[tempRow][tempCol].substr(1, 1) == CURRENTPLAYER)) {
		tempRow++;
		tempCol--;
		counter++;
	}
	/* forward track */
	tempRow = row - 1, tempCol = col + 1;
	while ((tempRow >= 0 && tempCol < BOARDCOLS) &&
		(board[tempRow][tempCol].substr(1, 1) == CURRENTPLAYER)) {
		tempRow--;
		tempCol++;
		counter++;
	}
	if (counter >= COUNT) {
		return true;
	}
	return false;
}

bool gameOver() {
	for (int i = 0; i < BOARDROWS; i++) {
		for (int j = 0; j < BOARDCOLS; j++) {
			if (board[i][j] == "|_|") {
				return false;
			}
		}
	}
	return true;
}

void printBoard() {
	for (int i = 0; i < BOARDROWS; i++) {
		cout << "\t";
		for (int j = 0; j < BOARDCOLS; j++) {
			cout << board[i][j];
			if (j == BOARDCOLS - 1) {
				cout << endl;
			}
			else {
				cout << " ";
			}
		}
	}
}


void nextPlayer() {
	if (CURRENTPLAYER == playerOne) {
		CURRENTPLAYER = playerTwo;
	}
	else {
		CURRENTPLAYER = playerOne;
	}
}
