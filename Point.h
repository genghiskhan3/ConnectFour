using namespace std;

class Point{
// Public variables and methods
public:
	Point(int direction, int run, int row, int col);
	int getDirection();
	int getRun();
	int getRow();
	int getCol();

// Private variables and methods
private:
	const int direction, run, row, col;
};

// Point constructor
Point::Point(int direction, int run, int row, int col)
	: direction(direction), run(run), row(row), col(col)
{

}

// Accessor method for direction variable
int Point::getDirection(){
	return this->direction;
}

// Accessor method for run variable
int Point::getRun(){
	return this->run;
}

// Accessor method for row variable
int Point::getRow(){
	return this->row;
}

// Accessor method for col variable
int Point::getCol(){
	return this->col;
}
