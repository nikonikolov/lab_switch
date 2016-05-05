#include "Snake_t.h"

Snake_t::Snake_t(const int& width, const int& height) : 
	d_width(width), d_height(height), prev_dir(dir_right){
		reset();
}

void Snake_t::gen_target(){
	target.set_coordinates(rand()%d_width, rand()%d_height);
}

void Snake_t::move(direction_t dir){

	list<Point>::iterator it_nose, it_tail;
	list<Point>::reverse_iterator rit_current, rit_next;

	// reverse list if opposite direction chosen
	if((prev_dir==dir_up && dir==dir_down) || (prev_dir==dir_down && dir==dir_up) || 
					(prev_dir==dir_left && dir==dir_right) || (prev_dir==dir_right && dir==dir_left)) 	location.reverse();

	it_nose = location.begin();
	it_tail = --location.end();

	Point target_got(*it_tail);
	Point new_nose(*it_nose);

	prev_dir = dir;

	// Get the new_nose
	if 		(dir==dir_up)		new_nose.y = ((new_nose.y) - 1 + d_height)%d_height;
	else if (dir==dir_down)		new_nose.y = ((new_nose.y) + 1)%d_height;
	else if	(dir==dir_left)		new_nose.x = ((new_nose.x) - 1 + d_width)%d_width;
	else if (dir==dir_right)	new_nose.x = ((new_nose.x) + 1)%d_width;

	// Move the whole snake
	for(rit_current = location.rbegin(), rit_next = ++location.rbegin(); rit_current != location.rend(); ++rit_current, ++rit_next){
		if(new_nose==*rit_current){
				reset();
				return;
		}

		if(rit_next!=location.rend()) *rit_current=*rit_next;
		else						  *rit_current=new_nose;
	}

	// Check if target is captured
	if(*it_nose==target){
		location.push_back(target_got);
		gen_target();
	} 
}

void Snake_t::reset(){
	location.clear();
	location.push_back(Point(2,0));
	location.push_back(Point(1,0));
	location.push_back(Point(0,0));
	gen_target();
	prev_dir=dir_right;
}


void Snake_t::printout(Adafruit_SSD1306_Spi& gOLED){
	//gOLED.clearDisplay();
	list<Point>::iterator it;
	for(it = location.begin(); it != location.end(); ++it){
		gOLED.fillGridPixel(it->x, it->y,1);
	}

	gOLED.fillGridPixel(target.x, target.y, 1);
}

