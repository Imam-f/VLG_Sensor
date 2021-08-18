#include "mbed.h"
 
DigitalOut myled(LED1);
DigitalIn pb(PA_0);
// SPST Pushbutton demo using internal PullUp function
// no external PullUp resistor needed
// Pushbutton from PA_0 to GND.
int main() {
    pb.mode(PullUp);
    while(1) {
        myled = pb;
        printf("%d\n\r",pb.read());
        wait_ms(1000);
    }
}