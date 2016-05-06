#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "Switch_h.h"
#include "Snake_t.h"


// Display interface pin definitions
#define D_MOSI_PIN p5
#define D_CLK_PIN p7
#define D_DC_PIN p8
#define D_RST_PIN p9
#define D_CS_PIN p10

Serial pc(USBTX, USBRX);

// Switch input definition
#define SW_PIN2 p21
#define SW_PIN3 p22
#define SW_PIN4 p23
#define SW_PIN5 p24
#define SWITCHES 4

//an SPI sub-class that sets up format and clock speed
class SPIPreInit : public SPI
{
public:
    SPIPreInit(PinName mosi, PinName miso, PinName clk) : SPI(mosi,miso,clk)
    {
        format(8,3);
        frequency(2000000);
    };
};


//Output for the alive LED
DigitalOut alive(LED1);

/* ============================================ Switch related data ============================================ */

//Switch sampling timer
Ticker swtimer;
void tout();
volatile uint16_t update=0;

Switch_h swins[] = {    Switch_h(SW_PIN2), 
                        Switch_h(SW_PIN3), 
                        Switch_h(SW_PIN4), 
                        Switch_h(SW_PIN5) 
                    };

/* ============================================ Wave generation data ============================================ */

volatile uint32_t half_period=0;
inline bool almost_equals(const double& a, const double& b);
DigitalOut wavegen(p20);
Ticker wtimer;
void gen_wave();        // calculates frequency and attaches interrupt
void toggle_wave();     // function called on interrupt


/* ============================================ Snake related data ============================================ */

Ticker snake_t_timer;
void Snake_t_move();
volatile direction_t dir = dir_right;
volatile uint8_t display_update=0;

/* ============================================ OLED related data ============================================ */

//Initialise SPI instance for communication with the display
SPIPreInit gSpi(D_MOSI_PIN,NC,D_CLK_PIN); //MOSI,MISO,CLK

//Initialise display driver instance
Adafruit_SSD1306_Spi gOled1(gSpi,D_DC_PIN,D_RST_PIN,D_CS_PIN,64,128); //SPI,DC,RST,CS,Height,Width

int main() { 
    

    //Attach switch sampling timer ISR to the timer instance with the required period
    swtimer.attach_us(&tout, SW_PERIOD);
    
    snake_t_timer.attach(&Snake_t_move, 0.2);    

    //Initialisation
    gOled1.setRotation(2); //Set display rotation
    gOled1.clearDisplay(); //Clear the display
  
    gOled1.setGridSize(4);  // set the size of a grid pixel for the game
    uint8_t grid_w = gOled1.get_grid_w();
    uint8_t grid_h = gOled1.get_grid_h();

    Snake_t snake(grid_w, grid_h);

    
    //Main loop
    while(1)
    {
        //Has the update flag been set?       
        if (update) {

            //Clear the display buffer
            gOled1.clearDisplay(); 

            gOled1.setTextCursor(0,0);
            //Clear the update flag
            update = 0;
            for(int i=0; i<SWITCHES; i++){
                //gOled1.printf("%u", swins[i].get_times_touched());
                gOled1.printf("%f %f\n", swins[i].get_frequency(), swins[i].get_tresh());
                //gOled1.printf("%f kHz %f %u\n", swins[i].get_frequency(), swins[i].get_tresh(), swins[i].get_times_touched());
            }

            for(int i=0; i<SWITCHES; i++){
                gOled1.printf("%u", swins[i].get_times_touched());
                //gOled1.printf("%f %u\n", swins[i].get_frequency(), swins[i].get_times_touched());
                //gOled1.printf("%f kHz %f %u\n", swins[i].get_frequency(), swins[i].get_tresh(), swins[i].get_times_touched());
            }

            //gOled1.printf("%u\n", dir);
            
            //Copy the display buffer to the display
            gOled1.display();
            
            //Toggle the alive LED
            alive = !alive;
        }
        /*
        if(display_update) {
            //Clear the display buffer
            gOled1.clearDisplay(); 

            //Clear the update flag
            display_update = 0;
            
            snake.move(dir);                    // make snake move
            snake.printout(gOled1);             // print new snake state

            //Copy the display buffer to the display
            gOled1.display();
            
            //Toggle the alive LED
            alive = !alive;
        }
        */
    }
}


//Interrupt Service Routine for the switch sampling timer
void tout() {
    for(int i=0; i<SWITCHES; i++){
        swins[i].sample();
        if(swins[i].get_touching()) dir=(direction_t)i;
    }
    //Trigger a display update in the main loop
    //update = 1;
    update=1;
}

void Snake_t_move(){
    display_update = 1;
}


void gen_wave(){
    uint32_t freqency = swins[0].get_times_touched()*1000 + swins[1].get_times_touched()*100 + 
                            swins[2].get_times_touched()*10 + swins[3].get_times_touched();
    //uint32_t half_period = (uint32_t) (1000000/(float)(2*freqency));
    uint32_t new_half_period = (uint32_t) (500000/freqency);    // in microseconds
   
    if(!almost_equals(half_period, new_half_period)){
        half_period = new_half_period;
        wtimer.detach();
        if(half_period) wtimer.attach_us(&toggle_wave, half_period);
    } 
}

void toggle_wave(){
    wavegen=!wavegen;
}

bool almost_equals(const double& a, const double& b){
    return fabs(a - b) <= 0.01;
}
