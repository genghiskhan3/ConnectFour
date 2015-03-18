#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include "Point.h"
using namespace std;

class Grid{
public:
	Grid();
	bool checkForWinner(char symbol);
	void displayGrid();
	bool isEmpty();
	void insert(char symbol, int col);
	bool validMove(int col);
	bool stalemate();
	bool firstComputerMove();

private:
	const int ROWS = 6;
	const int COLS = 7;
	char matrix[6][7];
	void initializeMatrix();
	int directionFinder(int x, int y);

};

// Testted and it works
Grid::Grid(){
	initializeMatrix();
}

// Tested and it works
void Grid::initializeMatrix(){
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			matrix[r][c] = '_';
		}
	}
}

// Tested and it works
void Grid::displayGrid(){
	string output = "";
	output += "    1  2  3  4  5  6  7\n\n";
	for (int r = 0; r < ROWS; r++){
		//ostringstream oss;
		//int curRow = r + 1;
		//oss << curRow;
		//output += oss.str();
		output += "    ";
		for (int c = 0; c < COLS; c++){
			output += matrix[r][c];
			output += "  ";
		}
		output += "\n";
	}
	cout << output << endl;
}

// Tested and it all works
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

// Tested and it works correctly
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


// Tested and it works
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

// Tested and works correctly
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

//Tested and works correctly
void Grid::insert(char symbol, int col){
	col--;
	for (int r = ROWS - 1; r >= 0; r--){
		if (matrix[r][col] == '_'){
			matrix[r][col] = symbol;
			break;
		}
	}
}

// Tested and works correctly
bool Grid::stalemate(){
	bool stale = true;
	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLS; c++){
			if (matrix[r][c] == '_'){
				stale = false;
				return stale;
			}
		}
	}
	return stale;
}

// Not neccessary now
bool Grid::firstComputerMove(){
	int i = 0;
	for (int c = 0; c < COLS; c++){
		if (matrix[ROWS - 1][c] != '_') i++;
	}
	if (i == 1) return true;
	else return false;
}



