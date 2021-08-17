#include "mbed.h"
#include "AMG8833.h"
# include "Ping.h"

Serial pc(USBTX,USBRX);

Adafruit_AMG88xx amg( PB_3, PB_10);
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];


Ping Pingerfm(PC_8);
Ping Pingerbaru(PA_15);
Ping Pingerfr(PA_14);
Ping Pingerl(PD_2);

AnalogIn UV1(PC_0);

InterruptIn in(PA_0);
DigitalOut s0(PA_13), s1(PA_14); // s2(p7), s3(p8)
BusOut setColor(PA_15, PC_15); //(LSB pin,..., MSB pin): (s3, s2). Red: 0, Blue: 1, Clear: 2, Green: 3.
Timer t;

float period = 0; // This is the period between interrupts in microseconds
float freq = 0;
int n;
int color; // Color


void print() {  // Print to PC
    switch (color) {
        case 0:
            pc.printf(" Red: \t\t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 1:
            pc.printf(" Blue: \t\t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 2:
            pc.printf(" Clear: \t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 3:
            pc.printf(" Green: \t%.2f Hz, \t%.2f us\r\n", freq, period);
            pc.printf("\r\n");
            break;
    }
}


void time() {
    if (n>99) { // Wait 100 interrupts
        period = t.read_us()/(float)n; // Get time
        freq = (1/period)*1000000;   // Convert period (in us) to frequency (Hz). Works up to 100kHz.
        n = 0;

        print(); // Print values to PC

        //color++;
        //if (color > 3) color = 0;
        //setColor = color;
        
        wait(0.5);
        t.reset(); // Reset timer and wait for next interrupt
    }
    n++;
}



int main() {
    // AMG
     wait(0.01);
     pc.printf("Setup");
 
    while (1) {

        amg.begin();
        wait(1) ;
        //read all the pixels
        amg.readPixels(pixels);
        
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(pixels[(i*8) + j] > 40){
                    pc.printf("*  ");
                }
                else {
                    pc.printf("|  ");
                }
            }
            pc.printf("\n\r");
        }
        pc.printf("\n\r");
        pc.printf("\n\r");

    }
}
 
 
