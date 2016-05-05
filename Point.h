#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point{

public:
	Point();
	Point(const int& x_in, const int& y_in);
	Point(const Point& p_in);
	~Point();
	
	inline void set_coordinates(const int& x_in, const int& y_in);

	inline int get_x();
	inline int get_y();
	
	inline int origin_dist() const;
	//void origin_symmetric();

	inline void translate_y(const int& delta_y);
	inline void translate_x(const int& delta_x);
	inline void translate(const Point& p2);
	
	inline int dist(const Point& p_in) const;
	inline int dist_sq(const Point& p_in) const;

	friend bool operator==(const Point& p1, const Point& p2);
	friend bool operator!=(const Point& p1, const Point& p2);
	void operator=(const Point& p2);
/*
	friend bool operator<(const Point& p1, const Point& p2);
*/

	int x;
	int y;

private:

};

void Point::set_coordinates(const int& x_in, const int& y_in){
	x = x_in;
	y = y_in;
}

int Point::get_x(){
	return x;
}

int Point::get_y(){
	return y;
}

int Point::origin_dist() const{
	return sqrt(pow(x,2) + pow(y,2));
}

int Point::dist(const Point& p_in) const{
	return sqrt( pow((x-p_in.x),2) + pow((y-p_in.y),2) );
}

int Point::dist_sq(const Point& p_in) const{
	return pow((x-p_in.x),2) + pow((y-p_in.y),2);
}

void Point::translate_y(const int& delta_y){
	y += delta_y;
}

void Point::translate_x(const int& delta_x){
	x += delta_x;
}


#endif
