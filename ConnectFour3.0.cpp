#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#define NOMINMAX
#include <windows.h>
#include "Grid.h"
#include "Player.h"
#include "VariablePrint.h";
using namespace std;

int main(){

	VariablePrint varPrint;

	// Neatly display a welcoming message that explains the game and its features
	varPrint.setString("*********************************************************************");
	varPrint.veryFastPrint();
	varPrint.endLine();
	varPrint.setString("*  Welcome to Connect Four. The goal of the game is to place tokens *");
	varPrint.fastPrint();
	varPrint.endLine();
	varPrint.setString("*  in columns and to try to place four in a row. The tokens may be  *");
	varPrint.fastPrint();
	varPrint.endLine();
	varPrint.setString("*  connected horizontally, diagonally, and vertically. You have     *");
	varPrint.fastPrint();
	varPrint.endLine();
	varPrint.setString("*  the option to either play a computer or with a friend. ENJOY!!!! *");
	varPrint.fastPrint();
	varPrint.endLine();
	varPrint.setString("*********************************************************************");
	varPrint.veryFastPrint();
	varPrint.endLine();
	varPrint.endLine(); varPrint.endLine();


	Sleep(1000);

	// boolean statements used to determine the flow of the program
	bool twoPlayer = true;
	bool validInput = false;


	// Prompt the user to select a game type
	// Two types: Two player and single player
	// Only accepts valid input and continues to prompt the user untill correct data is entered
	while (!validInput){
		string pChoice;
		varPrint.setString("Enter 1 for one player and 2 for two player: ");
		varPrint.mediumPrint();
		getline(cin, pChoice);
		if (atoi(pChoice.c_str()) != 1 && atoi(pChoice.c_str()) != 2){
			varPrint.endLine(); varPrint.endLine();
			varPrint.setString("Sorry that is not an acceptable input, please try again");
			varPrint.mediumPrint();
			varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
			Sleep(1500);
		}
		else if (atoi(pChoice.c_str()) == 1){
			varPrint.endLine(); varPrint.endLine();
			twoPlayer = false;
			validInput = true;
		}
		else{
			cout << "\n\n";
			validInput = true;
		}
	}


	// If the user has chosen to play the two player version then the program will execute this if statment
	if (twoPlayer){

		// This code prompts the two users at the beginning of the game to enter their information
		// Also checks to make sure none of the entered information will interfere with the design
		char playerOneSymbol;
		string playerOneName;
		char playerTwoSymbol;
		string playerTwoName;
		bool validInfoFields = false;
		while (!validInfoFields){
			string tempSymbol;
			varPrint.setString("Player one, please choose a one character symbol that you would like to represent your pieces with: ");
			varPrint.mediumPrint();
			getline(cin, tempSymbol);
			playerOneSymbol = tempSymbol[0];
			varPrint.endLine();
			varPrint.setString("Player one, please enter your name: ");
			varPrint.mediumPrint();
			getline(cin, playerOneName);
			varPrint.endLine();
			varPrint.setString("Player two, please choose a one character symbol that you would like to represent your pieces with: ");
			varPrint.mediumPrint();
			getline(cin, tempSymbol);
			playerTwoSymbol = tempSymbol[0];
			varPrint.endLine();
			varPrint.setString("Player two, please enter your name: ");
			varPrint.mediumPrint();
			getline(cin, playerTwoName);
			varPrint.endLine(); varPrint.endLine();

			if (playerOneSymbol == '_' || playerTwoSymbol == '_'){
				varPrint.endLine();
				varPrint.setString("Sorry that is not an acceptable symbol, please try again");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
				Sleep(500);
			}
			else if (playerOneName.compare(playerTwoName) == 0 || playerOneSymbol == playerTwoSymbol){
				varPrint.endLine();
				varPrint.setString("Sorry you can not have matching names or symbols, please try again");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
				Sleep(500);
			}
			else{ 
				validInfoFields = true;
			}
		}

		Player playerOne(playerOneSymbol, playerOneName);	// Initialize the first player
		Player playerTwo(playerTwoSymbol, playerTwoName);	// Initialize the second player

		Grid grid;		// Initalize the grid


		// This block of code randomly selects which player will go first by using random numbers
		srand(time(NULL));
		bool playerOnesTurn = true;
		if ((rand() % 100) % 2 == 0){ 
			playerOnesTurn = false; 
		}


		bool winner = false;
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
			}
			else{
				curSymbol = playerTwo.getSymbol();
				curName = playerTwo.getName();
			}


			string checkMove;		// Used to make sure the input is a valid integer and wont create an error
			int move;				// If the input is an integer the string is converted to this int
			bool valid = false;		// Bool used to flag invalid input and make sure valid input is entered

			// Loop will run unitl a valid move is entered by the current user
			while (!valid){
				if (playerOnesTurn){ 
					varPrint.endLine();
					varPrint.setString(playerOne.requestMove());
					varPrint.fastPrint();
				}
				else { 
					varPrint.endLine();
					varPrint.setString(playerTwo.requestMove());
					varPrint.fastPrint();
				}

				cin >> checkMove;
				if (atoi(checkMove.c_str()) != 0){
					move = atoi(checkMove.c_str());
					valid = grid.validMove(move);
				}
				else{
					valid = false;
				}

				if (!valid){ 
					varPrint.endLine();
					varPrint.setString("Sorry that is not a valid move, please enter a new move");
					varPrint.mediumPrint();
					varPrint.endLine();
					Sleep(1000);
				}
			}

			// Inserts the players move into the grid
			grid.insert(curSymbol, move);

			// neatly displays the grid
			Sleep(1000);
			cout << "\n\n\n";
			//varPrint.printGrid(grid);
			grid.displayGrid();
			cout << "\n";
			varPrint.setString(curName + " chose column " + (to_string(move)) + " this turn");
			varPrint.mediumPrint();
			varPrint.endLine(); varPrint.endLine();
			Sleep(1000);
			

			// Checks every iteration to see if there is a draw
			draw = grid.stalemate();
			if (draw){ 
				break; 
			}

			// Checks every iteration to see if there is a winner
			winner = grid.checkForWinner(curSymbol);


			// if there is a winner then the game is over
			if (winner){
				break;
			}

			// make it the other users turn the next time around
			if (playerOnesTurn){ 
				playerOnesTurn = false;
			}
			else{ 
				playerOnesTurn = true; 
			}
		}

		// Output endgame information to the users
		if (playerOnesTurn && !draw){ 
			varPrint.endLine(); varPrint.endLine();
			varPrint.setString("CONGRATULATIONS " + playerOne.getName() + " you are the winner");
			varPrint.mediumPrint();
			varPrint.endLine();
		}
		else if (!playerOnesTurn && !draw){
			varPrint.endLine(); varPrint.endLine();
			varPrint.setString("CONGRATULATIONS " + playerTwo.getName() + " you are the winner");
			varPrint.mediumPrint();
			varPrint.endLine();
		}
		else{ 
			varPrint.endLine();
			varPrint.setString("The match ends in a draw");
			varPrint.mediumPrint();
			varPrint.endLine();
		}


	}
	else{
		// This code will execute if the player has decided to play the one player version


		// prompt the player for thier name and the symbol they want to use
		// make sure that the information is valid and only move on if it is
		char playerOneSymbol;
		string playerOneName;
		bool validInfoFields = false;
		while (!validInfoFields){
			string tempSymbol;
			varPrint.setString("Player one, please choose a one character symbol that you would like to represent your pieces with: ");
			varPrint.mediumPrint();
			getline(cin, tempSymbol);
			playerOneSymbol = tempSymbol[0];
			varPrint.endLine();
			varPrint.setString("Player one, please enter your name: ");
			varPrint.mediumPrint();
			getline(cin, playerOneName);
			varPrint.endLine(); varPrint.endLine();

			if (playerOneSymbol == '@'){
				varPrint.endLine(); varPrint.endLine();
				varPrint.setString("Sorry that is the computers symbol, please select again");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
				Sleep(1000);
			}
			else if (playerOneSymbol == '_'){
				varPrint.endLine(); varPrint.endLine();
				varPrint.setString("Sorry that is not an acceptable symbol, please select agian");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
				Sleep(1000);
			}
			else if (playerOneName.compare("The Computer") == 0){
				varPrint.endLine(); varPrint.endLine();
				varPrint.setString("Sorry that is the computers name");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine(); 
				Sleep(1000);
			}
			else{
				validInfoFields = true;
			}
		}

		// Initialize the player object
		Player playerOne(playerOneSymbol, playerOneName);

		// initialize the grid object, using the constructor that takes playerOneSymbol as a parameter
		Grid grid(playerOneSymbol);


		// Ask the user what difficulty they would like to play on
		// Make sure that choice is a valid choice
		// Assign the specified diffuculty as the level variable
		bool validDifficulty = false;
		string getDifficulty;
		int level = 0;
		while (!validDifficulty){
			varPrint.endLine();
			varPrint.setString("What difficulty would you like to play on ?");
			varPrint.fastPrint();
			varPrint.endLine();
			varPrint.setString("1. Easy");
			varPrint.fastPrint();
			varPrint.endLine();
			varPrint.setString("2. Medium");
			varPrint.fastPrint();
			varPrint.endLine();
			varPrint.setString("3. Hard");
			varPrint.fastPrint();
			varPrint.endLine();
			varPrint.setString("4. Impossible (WARNING: Computational speed is slightly slow)");
			varPrint.fastPrint();
			varPrint.endLine();
			varPrint.endLine();
			varPrint.setString("Please select an option (1-4): ");
			varPrint.fastPrint();
			getline(cin, getDifficulty);

			if (atoi(getDifficulty.c_str()) >= 1 && atoi(getDifficulty.c_str()) <= 4){
				int difficulty = atoi(getDifficulty.c_str());
				if (difficulty == 1){
					level = 1;
					Sleep(500);
					varPrint.endLine(); varPrint.endLine();
					varPrint.setString("You have chosen to play on easy, good luck");
					varPrint.mediumPrint();
					varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
					Sleep(500);
				}
				else if (difficulty == 2){
					level = 3;
					Sleep(500);
					varPrint.endLine(); varPrint.endLine();
					varPrint.setString("You have chosen to play on medium, good luck");
					varPrint.mediumPrint();
					varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
					Sleep(500);
				}
				else if (difficulty == 3){
					level = 5;
					Sleep(500);
					varPrint.endLine(); varPrint.endLine();
					varPrint.setString("You have chosen to play on hard, good luck");
					varPrint.mediumPrint();
					varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
					Sleep(500);
				}
				else {
					level = 6;
					Sleep(500);
					varPrint.endLine(); varPrint.endLine();
					varPrint.setString("You have chosen to play on impossible, good luck");
					varPrint.mediumPrint();
					varPrint.endLine(); varPrint.endLine(); varPrint.endLine();
					Sleep(500);
				}
				validDifficulty = true;
			}
			else{
				varPrint.endLine(); varPrint.endLine();
				varPrint.setString("Sorry that is not a valid input, please try again");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine();
				Sleep(500);
			}
		}

		// Set the chosen level
		// The AI will use this value to change the difficulty of its playing style
		grid.setLevel(level);


		// Randomly select who has the first turn, either the player or the computer
		srand(time(NULL));
		bool playerOnesTurn = true;
		if ((rand() % 100) % 2 == 0){ 
			playerOnesTurn = false; 
		}

		
		// This is the playing of the game
		// This will continue the flow of the game and switch between turns until there is a winner or draw
		bool draw = false;
		bool winner = false;
		while (true){

			// Store the current players name and grid symbol
			char curSymbol;
			string curName;
			if (playerOnesTurn){
				curSymbol = playerOne.getSymbol();
				curName = playerOne.getName();
			}
			else{
				curSymbol = grid.getAISymbol();
				curName = grid.getAIName();
			}


			// If it is the players turn then request them to make a move and make sure it is valid
			// If it is the computers turn get the move that the computer views as best
			int move;
			if (playerOnesTurn){
				string checkMove;		// Used to make sure the input is a valid integer and wont create an error

				bool valid = false;		// Bool used to flag invalid input and make sure valid input is entered

				// Loop will run unitl a valid move is entered by the current user
				while (!valid){
					varPrint.endLine();
					varPrint.setString(playerOne.requestMove());
					varPrint.fastPrint();

					cin >> checkMove;
					if (atoi(checkMove.c_str()) != 0){
						move = atoi(checkMove.c_str());
						valid = grid.validMove(move);
					}
					else{
						valid = false;
					}

					if (!valid){ 
						varPrint.endLine();
						varPrint.setString("Sorry that is not a valid move, please enter a new move");
						varPrint.mediumPrint();
						varPrint.endLine();
						Sleep(1000);
					}
				}
			}
			else{
				if (level >= 5){
					varPrint.endLine();
					varPrint.setString("It is the computers turn to make a move");
					varPrint.mediumPrint();
					varPrint.endLine();
					Sleep(500);
					varPrint.setString("The computer is thinking");
					varPrint.mediumPrint();
					Sleep(1000);
					cout << "....";
					Sleep(1000);
					cout << "....";
					Sleep(1000);
					cout << "....";
					Sleep(1000);
					cout << "....";
					Sleep(1000);
					cout << "....";
					Sleep(1000);
					cout << "....\n";
				}
				else{
					varPrint.endLine();
					varPrint.setString("It is the computers turn to make a move");
					varPrint.mediumPrint();
					varPrint.endLine();
					Sleep(500);
					varPrint.setString("The computer is thinking");
					varPrint.mediumPrint();
					Sleep(1000);
					cout << "....";
					Sleep(1000);
					cout << "....\n";
				}
				move = grid.findMoveAI();
			}


			// Insert the move into the grid for either the player or computer
			grid.insert(curSymbol, move);


			// There are two different display methods, one for the computer and the other for the player
			if(!playerOnesTurn){
				Sleep(500);
				cout << "\n\n\n\n";
				grid.displayGrid();
				cout << "\n";
				varPrint.setString("The Computer chose column " + (to_string(move)) + " this turn");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine();
				Sleep(1000);
			}
			else{
				cout << "\n\n\n";
				grid.displayGrid();
				cout << "\n";
				varPrint.setString(curName + " chose column " + (to_string(move)) + " this turn");
				varPrint.mediumPrint();
				varPrint.endLine(); varPrint.endLine();
				Sleep(1000);
			}


			// Check to see if there is a draw
			// If so, break the loop because play is over
			draw = grid.stalemate();
			if (draw){ 
				break; 
			}

			// Check to see if there is a winner
			// If so, break the loop because play is over
			winner = grid.checkForWinner(curSymbol);
			if (winner) {
				break;
			}


			// Switch between the players turns
			// They alternate turns
			if (playerOnesTurn){ 
				playerOnesTurn = false; 
			}
			else{ 
				playerOnesTurn = true; 
			}
		}

		// Output the endgame information for the user to see the results
		if (playerOnesTurn && !draw){
			varPrint.endLine(); varPrint.endLine();
			varPrint.setString("CONGRATULATIONS " + playerOne.getName() + " you are the winner");
			varPrint.mediumPrint();
			varPrint.endLine();
		}
		else if (!playerOnesTurn && !draw){ 
			varPrint.endLine(); varPrint.endLine();
			varPrint.setString("CONGRATULATIONS " + grid.getAIName() + " is the winner");
			varPrint.mediumPrint();
			varPrint.endLine();
		}
		else{ 
			varPrint.endLine(); varPrint.endLine();
			varPrint.setString("The match ends in a draw");
			varPrint.mediumPrint();
			varPrint.endLine();
		}
	}
	return 0;
}
