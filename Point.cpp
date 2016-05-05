#include "Point.h"

Point::Point() : x(0.0), y(0.0) {}

Point::Point(const int& x_in, const int& y_in) : x(x_in), y(y_in) {}

Point::Point(const Point& p_in) : x(p_in.x), y(p_in.y) {}


Point::~Point(){}

bool operator==(const Point& p1, const Point& p2){
	return (p1.x==p2.x)&&(p1.y==p2.y);
}

bool operator!=(const Point& p1, const Point& p2){
	return !(p1==p2);
}

void Point::operator=(const Point& p2){
	if(this!=&p2){
		this->x=p2.x;
		this->y=p2.y;
	}
}

/*
void Point::origin_symmetric(){
	x=-x;
	y=-y;
}

	void Point :: translate(const Point& p2){
		x=x+p2.x;
		y=y+p2.y;
	}

bool operator<(const Point& p1, const Point& p2){
	return (p1.origin_dist() < p2.origin_dist());
}

*/


