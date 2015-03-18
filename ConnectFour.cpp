#include <iostream>
#include <string>
#include "Grid.h"
#include "Player.h"
using namespace std;

int main(){

	// This code prompts the two users at the beginning of the game to enter their information
	// Also checks to make sure none of the entered information will interfere with the design
	char playerOneSymbol;
	string playerOneName;
	char playerTwoSymbol;
	string playerTwoName;
	bool validInfoFields = false;
	while (!validInfoFields){
		string tempSymbol;
		cout << "Player one, please choose a one character symbol that you would like to represent your pieces with: ";
		cin >> tempSymbol;
		playerOneSymbol = tempSymbol[0];
		cout << "\nPlayer one, please enter your first name: ";
		cin >> playerOneName;
		cout << "\nPlayer two, please choose a one character symbol that you would like to represent your pieces with: ";
		cin >> tempSymbol;
		playerTwoSymbol = tempSymbol[0];
		cout << "\nPlayer two, please enter your first name: ";
		cin >> playerTwoName;

		if (playerOneSymbol == '_' || playerTwoSymbol == '_') cout << "\n\nSorry that is not an acceptable symbol\n\n\n\n";
		else if (playerOneName.compare(playerTwoName) == 0 || playerOneSymbol == playerTwoSymbol) cout << "\n\nSorry you can not have matching names or symbols\n\n\n\n";
		else validInfoFields = true;
	}

	Player playerOne(playerOneSymbol, playerOneName);	// Initialize the first player
	Player playerTwo(playerTwoSymbol, playerTwoName);	// Initialize the second player
			
	Grid grid;		// Initalize the grid

	bool winner = false;
	bool playerOnesTurn = true;
	bool draw = false;


	// This loop will run until there is a winner or the match ends in a draw
	// The loop will continue to prompt the user for their move choice and manage the flow of the game
	while (true){

		// Variables to keep track of the current players name and symbol
		char curSymbol;
		string curName;
		if (playerOnesTurn){
			curSymbol = playerOne.getSymbol();
			curName = playerOne.getName();
		} else{
			curSymbol = playerTwo.getSymbol();
			curName = playerTwo.getName();
		}
		
		
		string checkMove;		// Used to make sure the input is a valid integer and wont create an error
		int move;				// If the input is an integer the string is converted to this int
		bool valid = false;		// Bool used to flag invalid input and make sure valid input is entered

		// Loop will run unitl a valid move is entered by the current user
		while (!valid){
			if (playerOnesTurn) playerOne.requestMove();
			else playerTwo.requestMove();
			
			cin >> checkMove;
			if (atoi(checkMove.c_str()) != 0){
				move = atoi(checkMove.c_str());
				valid = grid.validMove(move);
			} else
				valid = false;

			if (!valid) cout << "\nSorry that is not a valid move, please enter a new move\n";
		}

		// Inserts the players move into the grid
		grid.insert(curSymbol, move);

		// neatly displays the grid
		cout << "\n\n\n\n";
		grid.displayGrid();
		cout << "\n\n";

		// Checks every iteration to see if their is a draw
		draw = grid.stalemate();
		if (draw) break;

		// Checks every iteration to see if their is a winner
		winner = grid.checkForWinner(curSymbol);

		if (winner) break;

		if (playerOnesTurn) playerOnesTurn = false;
		else playerOnesTurn = true;
	}

	// Output endgame information to the users
	if (playerOnesTurn && !draw) cout << "\n\nCONGRATULATIONS " << playerOne.getName() << " you are the winner" << endl;
	else if(!playerOnesTurn && !draw) cout << "\n\nCONGRATULATIONS " << playerTwo.getName() << " you are the winner" << endl;
	else cout << "\nThe match ends in a draw" << endl;
}
