#include <iostream>
#include <string>
using namespace std;

class Player{
public:
	Player(char symbol, string name);
	string getName();
	char getSymbol();
	void requestMove();

private:
	const char symbol;
	const string name;
};


// Tested and it works
Player::Player(char symbol, string name)
	:symbol(symbol), name(name)
{

}

// Tested and it works
string Player::getName(){
	return this->name;
}

//Tested and it works
char Player::getSymbol(){
	return this->symbol;
}

// Tested and it works correctly
// This method only prints out the request to make a move
// It does NOT accept any values or call the insert method in the Grid class
void Player::requestMove(){
	cout << "\n" << this->name << " it is your turn to move" << endl;
	cout << "Please select a column for your move (1-7): ";
}
