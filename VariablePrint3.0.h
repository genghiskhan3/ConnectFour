#include <string>
#include <iostream>
#define NOMINMAX
#include <Windows.h>
//#include "Grid.h";
using namespace std;

class VariablePrint{
public:
	VariablePrint();
	void verySlowPrint();
	void slowPrint();
	void mediumPrint();
	void fastPrint();
	void veryFastPrint();
	void setString(string s);
	void endLine();
	//void printGrid(Grid& grid);


private:
	string s;
	const int verySlow = 500;
	const int slow = 300;
	const int medium = 35;
	const int fast = 20;
	const int veryFast = 10;
};

VariablePrint::VariablePrint(){
	s = "";
}

void VariablePrint::setString(string s){
	this->s = s;
}

void VariablePrint::verySlowPrint(){
	for (char& c : s){
		cout << c;
		Sleep(verySlow);
	}
}

void VariablePrint::slowPrint(){
	for (char& c : s){
		cout << c;
		Sleep(slow);
	}
}

void VariablePrint::mediumPrint(){
	for (char& c : s){
		cout << c;
		Sleep(medium);
	}
}

void VariablePrint::fastPrint(){
	for (char& c : s){
		cout << c;
		Sleep(fast);
	}
}

void VariablePrint::veryFastPrint(){
	for (char& c : s){
		cout << c;
		Sleep(veryFast);
	}
}

void VariablePrint::endLine(){
	cout << "\n";
}

/*void VariablePrint::printGrid(Grid& grid){
	setString("    1  2  3  4  5  6  7");
	fastPrint();

	for (int r = 0; r < 6; r++){
		setString("    ");
		fastPrint();
		for (int c = 0; c < 7; c++){
			setString(grid.charAt(r, c) + "  ");
			fastPrint();
		}
		endLine();
	}
	endLine();
}*/
