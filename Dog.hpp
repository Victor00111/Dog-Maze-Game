#include <iostream>
#include <string.h>
using namespace std;

class Dog {
	friend class Board;
	string name; // for the dog's name
	int strength; //for the dog's current strength
	int x; // the x coordinate of where the dog is currently on the board
	int y; // the y coordinate of where the dog is currently on the board

public:
	Dog(string n); //constructor
	Dog(); //constructor
	bool changeStrength(int amt); //changes dog’s strength field
	void die(); // Death message when strength at or below 0
	void printDog(); // prints out info about dog
	void won(); // Won message for when dog is at end of evil forest
	void reset(); // Resets dog for restarting a new game
};


