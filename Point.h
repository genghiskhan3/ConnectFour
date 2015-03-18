using namespace std;

class Point{
public:
	Point(int direction, int run, int row, int col);
	int getDirection();
	int getRun();
	int getRow();
	int getCol();

private:
	int direction, run, row, col;
};

Point::Point(int direction, int run, int row, int col){
	this->direction = direction;
	this->run = run;
	this->row = row;
	this->col = col;
}

int Point::getDirection(){
	return this->direction;
}

int Point::getRun(){
	return this->run;
}

int Point::getRow(){
	return this->row;
}

int Point::getCol(){
	return this->col;
}
