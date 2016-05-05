#include "Switch_h.h"

Switch_h::Switch_h(const PinName& pin) : swin(pin), scounter(0), scount(0), frequency(0), 
												non_touch_freq(0), treshold(-1), nsamples(0), times_touched(0), touching(false){
    //Attach switch oscillator counter ISR to the switch input instance for a rising edge
	swin.rise(this, &Switch_h::sedge);
}

void Switch_h::sedge(){
	scounter++;
}

void Switch_h::sample(){
    //Read the edge counter into the output register
    scount = scounter;
    //Reset the edge counter
    scounter = 0;
    // Calculate the frequency
    frequency = float(scount/float(SW_PERIOD/1000));
    
    // Determine treshold
    if(nsamples<TRESHOLD_SAMPLES){
	    nsamples++;
    	if(nsamples>=TRESHOLD_MIN){
    		non_touch_freq+=frequency;
    	}
    	if(nsamples==TRESHOLD_SAMPLES){
    		non_touch_freq = non_touch_freq/float(TRESHOLD_SAMPLES-TRESHOLD_MIN+1);
    		treshold = non_touch_freq-1.5;
    	}
    }

    // Determine if touching and take additional action
    else{
    	if(frequency<treshold){
			if(!touching) times_touched++;
			if(times_touched==10) times_touched=0;
			touching=true;
		}
    	else touching=false;
    }
}

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

