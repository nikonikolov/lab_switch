#ifndef Switch_h_H
#define Switch_h_H

#include "mbed.h"
//Sampling period for the switch oscillator (us)
#define SW_PERIOD 20000 
#define TRESHOLD_SAMPLES 8
#define TRESHOLD_MIN 3


class Switch_h{

public:
	Switch_h(const PinName& pin);
	void sedge();
	void sample();

	inline bool get_touching();
	inline float get_frequency() const;
	inline float get_tresh() const;
	inline int get_times_touched() const;

private:
	InterruptIn swin;
	volatile uint16_t scounter;
	volatile uint16_t scount;
	volatile float frequency;

	volatile float non_touch_freq;
	volatile float treshold;
	volatile int nsamples;

	volatile int times_touched;
	volatile bool touching;
};

bool Switch_h::get_touching(){
	return touching;
}

float Switch_h::get_frequency() const{
	return frequency;
}

float Switch_h::get_tresh() const{
	return treshold;
}

int Switch_h::get_times_touched() const{
	return times_touched;
}


#endif

