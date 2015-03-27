#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <limits>
#include "Point.h"
using namespace std;

class Grid{
// All of the public methods used in the Grid class
public:
	Grid();
	bool checkForWinner(char symbol);
	void displayGrid();
	bool isEmpty();
	void insert(char symbol, int col);
	bool validMove(int col);
	bool stalemate();
	int findMoveAI();
	void undoMove(int col);

// All of the private variables and methods used in the grid class
private:
	const int ROWS = 6;
	const int COLS = 7;
	char matrix[6][7];
	void initializeMatrix();
	int directionFinder(int x, int y);
	const int WIN_VALUE = numeric_limits<int>::max();
	const int LOSE_VALUE = numeric_limits<int>::min();
	const int UNCERTAIN_VALUE = 0;
	const char AISymbol = '@';
	double moveValue(int col);
	double maxmin(int depth, int alpha, int beta,bool maximizingPlayer);
	double moveValue(int col);
	char playerSymbol;

};

// Grid constructor
// Takes no paramaters and simply calls the initializeMatrix() method
Grid::Grid(char playerSymbol){
	initializeMatrix();
	this->playerSymbol = playerSymbol;
}

Grid::Grid(){
	initializeMatrix();
}

// Method to initialize the matrix
// The matrix will initially be all '_' which will represent empty areas in the matrix
void Grid::initializeMatrix(){
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			matrix[r][c] = '_';
		}
	}
}

// Method to display the current state of the matrix to the user
void Grid::displayGrid(){
	string output = "";
	output += "    1  2  3  4  5  6  7\n\n";
	for (int r = 0; r < ROWS; r++){
		output += "    ";
		for (int c = 0; c < COLS; c++){
			output += matrix[r][c];
			output += "  ";
		}
		output += "\n";
	}
	cout << output << endl;
}

// Algorithm to check for a winner on the grid
// Implements the DFS algorithm to check for any runs of four within the matrix
bool Grid::checkForWinner(char symbol){
	int dx[] = { 1, -1, 0, 0, 1, -1, -1, 1 };
	int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
	bool found = false;

	for (int r = ROWS - 1; r >= 0; r--){
		for (int c = COLS - 1; c >= 0; c--){
			if (matrix[r][c] == symbol){
				Point start(-1, 1, r, c);
				queue<Point> q;
				q.push(start);

				while (!q.empty()){
					Point current = q.front();
					q.pop();
					if (current.getRun() == 4){
						found = true;
						return found;
					}

					if (current.getDirection() == -1){
						for (int i = 0; i < 8; i++){
							int newx = current.getRow() + dx[i];
							int newy = current.getCol() + dy[i];

							if (newx >= 0 && newx < ROWS && newy < COLS && newy >= 0 && matrix[newx][newy] == symbol){
								Point next(directionFinder(dx[i], dy[i]), current.getRun() + 1, newx, newy);
								q.push(next);
							}
						}
					} else{
						for (int i = 0; i < 8; i++){
							int newx = current.getRow() + dx[i];
							int newy = current.getCol() + dy[i];
							int d = directionFinder(dx[i], dy[i]);

							if (newx >= 0 && newx < ROWS && newy < COLS && newy >= 0 && matrix[newx][newy] == symbol && d == current.getDirection()){
								Point next(d, current.getRun() + 1, newx, newy);
								q.push(next);
							}
						}
					}
				}
			}
		}
	}
	return found;
}

// Method used only by the checkForWinner() method
// It simply returns the angle of the next possible move
// This is used to ensure that the DFS algorithm continues in the same direction when searching for a set of 4
int Grid::directionFinder(int x, int y){
	if (x == 1 && y == 0){
		return 0;
	}
	else if (x == -1 && y == 0){
		return 180;
	}
	else if (x == 0 && y == 1){
		return 90;
	}
	else if (x == 0 && y == -1){
		return 270;
	}
	else if (x == 1 && y == 1){
		return 45;
	}
	else if (x == -1 && y == 1){
		return 135;
	}
	else if (x == -1 && y == -1){
		return 225;
	}
	else {
		return 315;
	}
}


// Method to check to see if the grid is empty
bool Grid::isEmpty(){
	bool empty = true;
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			if (matrix[r][c] != '_'){
				empty = false;
				return empty;
			}
		}
	}
	return empty;
}

// Method to check to see if the users input is a valid move choice
// Checks:
// Choice is within the range of 1-7
// The current column is not already full
bool Grid::validMove(int col){
	col--;
	bool valid = false;
	if (col >= COLS || col < 0){
		valid = false;
	} else if (matrix[0][col] == '_'){
		valid = true;
	} else{
		valid = false;
	}
	return valid;
}

// Method to insert the user input into the matrix
// Starts from the bottom of the coulumn to mimic gravity and the games core concepts
void Grid::insert(char symbol, int col){
	col--;
	for (int r = ROWS - 1; r >= 0; r--){
		if (matrix[r][col] == '_'){
			matrix[r][col] = symbol;
			break;
		}
	}
}

void Grid::undoMove(int col){
	col--;
	for (int r = 0; r < ROWS; r++){
		if (matrix[r][col] != '_'){
			matrix[r][col] = '_';
			break;
		}
	}
}

// Method to check to see if their is a stalemate 
// Essentially searches the grid to make sure there is no empty space
// Only have to search the first row because of the concept of gravity again
bool Grid::stalemate(){
	bool stale = true;
	for (int c = 0; c < COLS; c++){
		if (matrix[0][c] == '_'){
			stale = false;
			return stale;
		}
	}
	return stale;
}

int Grid::findMoveAI(){
	double maxVal = numeric_limits<int>::min();
	int move = 0;
	
	for (int c = 1; c <= COLS; c++){
		if (validMove(c)){
			double curVal = moveValue(c);
			if (curVal > maxVal){
				maxVal = curVal;
				move = c;
				if (curVal == WIN_VALUE){
					break;
				}
			}
		}
	}
}

double Grid::moveVaule(int col){
	insert(AISymbol, col);
	
	double curVal = maxmin(4, numeric_limits<int>::min(), numeri_limits<int>::max(), false);
	
	undoMove(col);
	return curVal;
}

double Grid::maxmin(int depth, double alpha, double beta, bool maximizingPlayer){
	bool hasWinner = checkForWinner(AISymbol) || checkForWinner(playerSymbol);

	if (depth == 0 || hasWinner){
		double score = 0;
		if (hasWinner){
			if (checkForWinner(playerSymbol)){
				score = LOSS_VALUE;
			}
			else{
				score = WIN_VALUE;
			}
		}
		else{
			score = UNCERTAIN_VALUE;
		}
		return score / (MAX_DEPTH - depth + 1);
	}

	if (maximizingPlayer){
		for (int c = 1; c <= COLS; c++){
			if (grid->validMove(c)){
				insert(AISymbol, c);
				alpha = fmax(alpha, maxmin(depth - 1, alpha, beta, false));
				undoMove(c);
				if (beta <= alpha){
					break;
				}
			}
		}
		return alpha;
	}
	else{
		for (int c = 1; c <= COLS; c++){
			if (validMove(c)){
				insert(playerSymbol, c);
				beta = fmin(beta, maxmin(depth - 1, alpha, beta, true));
				undoMove(c);
				if (beta <= alpha){
					break;
				}
			}
		}
		return beta;
	}
}
