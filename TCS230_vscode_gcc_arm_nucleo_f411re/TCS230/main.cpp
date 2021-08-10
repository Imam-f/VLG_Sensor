/*
****************************************************
TCS230 test. COLOR LIGHT TO FREQUENCY CONVERTER.
Frequency is measured by interrupts.

Wiring: TCS230       mBed
         p1(s0)      p5
         p2(s1)      p6
         p7(s2)      p7
         p8(s3)      p8
         p6(out)     p9
p3(OE), p4(GND) tied to ground. p5(Vcc) tied to 3V3.

Author: Lluis Nadal. August 2011.
****************************************************
*/


#include "mbed.h"


InterruptIn in(PA_1);
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
            printf(" Red: \t\t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 1:
            printf(" Blue: \t\t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 2:
            printf(" Clear: \t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 3:
            printf(" Green: \t%.2f Hz, \t%.2f us\r\n", freq, period);
            printf("\r\n");
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

    in.mode(PullDown); // Set the pin to Pull Down mode.
    wait(1);
    n = 0;
    color = 0;
    // setColor = color;

    s0 = 0;
    s1 = 1; // Frequency 2% = 12 kHz full-scale.

    in.rise(&time);  // Set up the interrupt for rising edge
    t.start();       // Start the timer

    while (1) {

    }
}



