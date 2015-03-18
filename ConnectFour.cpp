#include <iostream>
#include <string>
#include "Grid.h"
#include "Player.h"
using namespace std;

int main(){

	char playerOneSymbol;
	string playerOneName;
	char playerTwoSymbol;
	string playerTwoName;
	bool validInfoFields = false;
	while (!validInfoFields){
		cout << "Player one, please choose a one character symbol that you would like to represent your pieces with: ";
		cin >> playerOneSymbol;
		cout << "\nPlayer one, please enter your first name: ";
		cin >> playerOneName;
		cout << "\nPlayer two, please choose a one character symbol that you would like to represent your pieces with: ";
		cin >> playerTwoSymbol;
		cout << "\nPlayer two, please enter your first name: ";
		cin >> playerTwoName;

		if (playerOneSymbol == '_' || playerTwoSymbol == '_') cout << "\n\nSorry that is not an acceptable symbol\n\n\n\n";
		else if (playerOneName.compare(playerTwoName) == 0 || playerOneSymbol == playerTwoSymbol) cout << "\n\nSorry you can not have matching names or symbols\n\n\n\n";
		else validInfoFields = true;
	}

	Player playerOne(playerOneSymbol, playerOneName);
	Player playerTwo(playerTwoSymbol, playerTwoName);

	Grid grid;

	bool winner = false;
	bool playerOnesTurn = true;
	bool stale = false;

	while (true){
		char curSymbol;
		string curName;
		if (playerOnesTurn){
			curSymbol = playerOne.getSymbol();
			curName = playerOne.getName();
		} else{
			curSymbol = playerTwo.getSymbol();
			curName = playerTwo.getName();
		}
		
		
		int move;
		bool valid = false;
		while (!valid){
			if (playerOnesTurn) playerOne.requestMove();
			else playerTwo.requestMove();
			

			cin >> move;

			valid = grid.validMove(move);

			if (!valid) cout << "\nSorry that is not a valid move, please enter a new move\n";
			

		}

		grid.insert(curSymbol, move);

		cout << "\n\n\n\n";
		grid.displayGrid();
		cout << "\n\n";

		stale = grid.stalemate();
		if (stale) break;

		winner = grid.checkForWinner(curSymbol);

		if (winner) break;

		if (playerOnesTurn) playerOnesTurn = false;
		else playerOnesTurn = true;
	}

	if (playerOnesTurn && !stale) cout << "\n\nCONGRATULATIONS " << playerOne.getName() << " you are the winner" << endl;
	else if(!playerOnesTurn && !stale) cout << "\n\nCONGRATULATIONS " << playerTwo.getName() << " you are the winner" << endl;
	else cout << "\n\The match ends in a draw" << endl;
}
