#include "Dog.hpp"
#include <iostream>
using namespace std;

Dog::Dog(string n) {
	/* Constructor, sets the name to be whatever name gets passed in and the
	*  strength to be 50
	*/
	name = n;
	strength = 50;
	x = 1;
	y = 1;
}
Dog::Dog() {
	// Constructor
	name == "Spike";
	strength = 50;
	x = 1;
	y = 1;
}
bool Dog::changeStrength(int amt) {
	/*changeStrength modifies the strength property by whatever amt is (basically adding here)
	* It then calls printDog method to print out current information about the dog.
	* It also checks to make sure that the dog object's strength is >0.
	* If the dog object's strength is 0 or less, it calls the die method.
	* It returns true if the strength is still >0 and false otherwise.
	*/
	strength += amt;
	if (amt == 0) {
		printDog();
	}
	if (strength > 0) {
		return true;
	}
	else {
		if (amt == 0) {
			die();
			return false;
		}
	}
}
void Dog::die() {
	cout << "Game Over. " << name << " is in dog heaven now :(. Maybe you could get him out next time?" << endl;
}
void Dog::printDog() {
// Prints out the basic information about the dog.
	cout << "Dog: "<< name << endl;
	cout << "Strength: " << strength << endl;
}
void Dog::won() {
	cout << "Congratulations, you navigated " << name << " out safely :)" << endl;
}
void Dog::reset() {
// Resets the strength and the x and y to 0 and 0.
	strength = 50;
	x = 1;
	y = 1;
}

