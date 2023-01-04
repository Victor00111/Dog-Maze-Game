#include "Board.hpp"
#include <iostream>
using namespace std;

Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;

	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % (size-2) + 1;
		starty = 0;
		endx = rand() % (size-2) + 1;
		endy = size-1;

		mydog.x = startx;
		mydog.y = starty+1;
		boardConfig();
		addFood();
		addTraps();
		mydog.printDog();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}


void Board::printBoard() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == '-') {
				cout << board[i][j] << '>';
			}
			else if (board[i][j] == 'T' && !debug) {
				cout << ' ' << ' ';
			}
			else {
				cout << board[i][j] << ' ';
			}
		}
		cout << endl;
	}
}

void Board::boardConfig() {
	int numWallsToAdd = 12;

	if (level == 'm') {
		numWallsToAdd = 18;
	}
	else if (level == 'h') {
		numWallsToAdd = 25;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = ' ';
		}
	}

	for (int j = 0; j < size; j++) {
		int addWall = rand() % 2;
		int wallsAdded = 0;
		if (addWall && j % 2 == 1) {
			while (wallsAdded < numWallsToAdd) {
				int i = rand() % 18 + 1;
				board[i][j] = '|';
				wallsAdded++;

			}
		}
	}

	for (int i = 0; i < size; i++) {
		int addWall = rand() % 2;
		int wallsAdded = 0;
		if (addWall && i %  2 == 1) {
			while (wallsAdded < numWallsToAdd) {
				int j = rand() % 18 + 1;
				board[i][j] = '_';
				wallsAdded++;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0 || j == size-1) {
				board[i][j] = '|';
				}
			if (i == 0 || i == size-1) {
				board[i][j] = '_';
			}
		}
	}
	board[startx][starty] = '-';
	board[startx][starty + 1] = 'D';
	board[endx][endy] = '-';
	board[endx][endy - 1] = 'E';
}


void Board::addFood() {
	int diff = 0;
	int numFood = 0;
	if (level == 'm') {
		diff = 2;
	}
	else if (level == 'h') {
		diff = 4;
	}
	while (numFood < size - diff) {
		int randx = (rand() % 18) + 1;
		int randy = (rand() % 18) + 1;
		if (board[randx][randy] == ' ') {
			board[randx][randy] = 'F';
			numFood++;
		}
	}
}

void Board::addTraps() {
	int diff = 0;
	int numTrap = 0;
	if (level == 'm') {
		diff = 5;
	}
	else if (level == 'h') {
		diff = 10;
	}
	while (numTrap < size + diff) {
		int randx = (rand() % 18) + 1;
		int randy = (rand() % 18) + 1;
		if (board[randx][randy] == ' ') {
			board[randx][randy] = 'T';
			numTrap++;
		}
	}
}


bool Board::moveDog(char c) {
	int tempX = mydog.x;
	int tempY = mydog.y;
	if (c == 'u') {
		mydog.x--;
	}
	else if (c == 'd') {
		mydog.x++;
	}
	else if (c == 'l') {
		mydog.y--;
	}
	else if (c == 'r') {
		mydog.y++;
	}
	else {
		cout << "Please enter a valid direction." << endl;
		mydog.printDog();
		return true;
	}
	if (mydog.x == endx && mydog.y == endy) {
		mydog.won();
		return false;
	}
	if (mydog.x == 0 || mydog.x == size-1 || mydog.y == 0 || mydog.y == size-1) {
		cout << "You cannot go outside of the border!" << endl;
		mydog.x = tempX;
		mydog.y = tempY;
		return true;
	}
	else if (board[mydog.x][mydog.y] == 'F') {
		int strengthGained = rand() % 16 + 2;
		cout << mydog.name << " eats food. He thinks it's delicious! +" << strengthGained << " Strength" << endl;
		mydog.changeStrength(strengthGained);
	}
	else if (board[mydog.x][mydog.y] == 'T') {
		int strengthLost = -(rand() % 16 + 2);
		cout << "Oh, no! " << mydog.name << " stepped into a trap! " << strengthLost << " Strength" << endl;
		mydog.changeStrength(strengthLost);
	}
	else if (board[mydog.x][mydog.y] == '|' || board[mydog.x][mydog.y] == '_') {
		if (mydog.strength > wallStrength) {
			string answer;
			cout << "Do you want to knock down that wall? It will cost 6 Strength." << endl;
			cin >> answer;
			if (answer == "yes" || answer == "y" || answer == "Yes" || answer == "Y") {
				mydog.changeStrength(-wallStrength);
			}
			else {
				mydog.changeStrength(-1);
				mydog.x = tempX;
				mydog.y = tempY;
			}
		}
		else {
			cout << mydog.name << " does not have enough Strength!" << endl;
			mydog.x = tempX;
			mydog.y = tempY;
		}
	}
	else {
		mydog.changeStrength(-2);
	}
	board[tempX][tempY] = ' ';
	board[mydog.x][mydog.y] = 'D';
	return mydog.changeStrength(0);
}


void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}
}

