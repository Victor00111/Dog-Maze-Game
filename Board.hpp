/*
 * Board.hpp
 *
 *  Created on: Feb 25, 2021
 *      Author: 13027
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "Dog.hpp"
#include <iostream>
#include <string.h>
using namespace std;

class Board {
	int size = 20;  //the square board's size
	char board[20][20]= {{'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9'},
			{'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0'},
			{'2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1'},
			{'3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2'},
			{'4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3'},
			{'5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4'},
			{'6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5'},
			{'7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'},
			{'8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7'},
			{'9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8'},
			{'0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9'},
			{'1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0'},
			{'2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1'},
			{'3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2'},
			{'4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3'},
			{'5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4'},
			{'6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5'},
			{'7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6'},
			{'8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7'},
			{'9','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8'}};

	int wallStrength;  //the amount of strength needed to take down part of the wall (6)
	int startx;  //Where the dog enters the board (randomly along the left side)
	int starty;  //again, the dog's y entrance to the board (0)
	int endx;  // THe goal location on the right side (random x value)
	int endy;  // will be size -1
	char level; //'e' for easy, 'm' for medium, 'h' for hard (user can input in the initAll() method)
	Dog mydog;  //the dog object that's moving through

	bool debug;

public:
	Board(char diff, string name, bool d);
	/* constructor - has as a parameter the level of difficulty, the name I'll give
	 * to my dog object, and whether debug mode is on or off
	 * This method calls the initAll method.
	 */
	Board(char diff, bool d);
	/* constructor - sets level of difficulty and the debug mode.  With this the
	 * dog constructor that doesn't require a name is called, so the default dog's
	 * name is fluffy (which is set in the dog's constructor)
	 * This method calls the initAll method.
	 */
	Board(bool d);
	/* for this constructor the level is set to be 'e' (which is the default), it calls
	 * the default dog constructor, and it calls the initAll method.
	 */
	void InitAll();
	/* Loops for each playing of the game, continuing
	 * as long as the user enters "yes", "Yes","y", or "Y".  It asks the user and
	 * sets the level of difficulty.  It finds the start and end square that the
	 * dog must traverse, it calls boardConfig to configure the board, it calls
	 * printBoard to see the board, it calls addFood and addTraps. And then it calls
	 * the playGame method to start the game.  It loops to continuously reset everything
	 * and play another round of the game for every time the user says they want to
	 * continue playing another round.
	 */
	void boardConfig();

	void printBoard();
	/* This method first uses the dog's printDog method to print out info about the dog, and then
	 * it prints out the board.
	 */

	void addFood();
	/* This method randomly adds food around the board.  For easy, I added the field size
	 * number of foods randomly around the board.  For medium, I added size-2 foods, and for
	 * hard I added size-4 foods.  The amount of strength the dog gets when they eat (aka
	 * move onto) the food is determined in the moveDog method.
	 */
	void addTraps();
	/* This method randomly adds traps around the board.  For easy I added size - 6 traps,
	 * for medium, I added size - 8 traps, and for hard I added size - 10 traps.  Note: Traps are
	 * only printed on the board when the game is in debug mode.  The amount of strength each trap
	 * saps from the dog is determined in the moveDog method when the dog moves on a Trap.
	 */
	void playGame();
	/* This method loops for every move the dog makes.  It asks whether the user wants to move up,
	 * down, left, or right.  It then calls the moveDog method with the character indicating which
	 * way the dog should move, and then it calls the printBoard method.
	 */
	bool moveDog(char c);
	/* Determines the new coordinates of the dog, based on the direction in which the
	 * dog wants to move (based on what c holds - u is up, d is down, l is left, r is right).
	 *
	 * If the dog is at the edge of the board, the dog should not move
	 *
	 * If the dog moves over food, a random number between 2 and 17 is generated, and the
	 * dog's changeStrength method is used to increase the dog's strength by the random amount.
	 *
	 * If the dog moves over the end of the board, the dog's won method is called and false is
	 * returned from this method.
	 *
	 * If the dog moves over a Trap, a random number between 2 and 17 is generated and the dog's
	 * changeStrength method is called with that negative number.  (Note that the changeStrength
	 * method returns a boolean indicating whether the dog's strength has gone to 0 or less, and
	 * thus the dog has died and the game is over. That boolean value is returned from this method).
	 *
	 * If the dog moves over a wall, the method checks to see if the dog has enough strength to
	 * knock down the wall (I made it cost 6 strength points to knock down a wall).  If the dog
	 * has enough strength, the user is asked, "Do you want to knock down that wall?"  If the user
	 * responds "yes", then the wall is knocked down, the dog moves into that square, adn the dog's
	 * strength decreases by 6.  If the answer is "no", the dog loses 1 strength point, just because.
	 *
	 * If the dog moves into a blank square, the dog loses 2 strength points using the changeStrength
	 * method (which, again, will return false if the dog has lost all their strength and died.
	 *
	 * NOTE: I am not concerned with the precise rules here.  If you want to change the range of
	 * random numbers for food, if you are worried about whether you still lose 2 strength points for
	 * moving even though you gained points for moving over food - I'm leaving that to your preference.
	 * I am concerned that you are using classes, objects, and object methods and accessing object
	 * fields correctly!
	 *
	 */
};



#endif /* BOARD_HPP_ */
