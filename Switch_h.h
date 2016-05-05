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

	bool get_touching();
	float get_frequency() const;
	float get_tresh() const;
	int get_times_touched() const;

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


#endif

