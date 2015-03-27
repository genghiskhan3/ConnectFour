#include <iostream>
#include <string>
using namespace std;

class Player{
	// Public variables and methods
public:
	Player(char symbol, string name);
	string getName();
	char getSymbol();
	string requestMove();

	// Private variables and methods
private:
	const char symbol;
	const string name;
};


// Player constructor
// Initializes the symbol and name variables as constants
Player::Player(char symbol, string name)
	:symbol(symbol), name(name)
{

}

// Accessor method for the name variable
string Player::getName(){
	return this->name;
}

// Accessor method for the symbol variable
char Player::getSymbol(){
	return this->symbol;
}

// Method to prompt the user to make a move
// This method only prints out the request to make a move
// It does NOT accept any values or call the insert method in the Grid class
string Player::requestMove(){
	string s = this->name + " it is your turn to move, Please select a column for your move (1-7): ";
	return s;
}
