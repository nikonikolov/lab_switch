#ifndef Snake_t_H
#define Snake_t_H

#include <vector>
#include <list>
#include "Point.h"
#include "Adafruit_SSD1306.h"

using std::vector;
using std::list;

enum direction_t{
	dir_up = 1,
	dir_down = 2,
	dir_left = 0,
	dir_right = 3
};


class Snake_t{
public:
	Snake_t(const int& width, const int& height);
	void move(direction_t dir);
	void printout(Adafruit_SSD1306_Spi& gOLED);

private:

	void gen_target();
	void reset();

	int d_width;
	int d_height;
	Point target;
	list<Point> location;

	direction_t prev_dir;
};


#endif



