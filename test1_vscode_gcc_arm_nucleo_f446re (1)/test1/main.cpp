#include "mbed.h"

DigitalOut relay(PA_1);
DigitalIn  Line1(PC_5);
DigitalIn  Line2(PH_1);

int digital[2];

int main() {
    while (1) {

        digital[0] = Line1.read();
        digital[1] = Line2.read();

        printf("Line : \n\r");
        printf("%d__%d\n\r",
                  digital[0], digital[1]);
        printf("_______________________________________________\n\r");


        relay = 0;
        printf("Relay %d is now off %d\r\n", relay.is_connected(),relay.read());
        wait_ms(1000);
        
        relay = 1;
        printf("Relay %d is now on %d\r\n", relay.is_connected(), relay.read());
        wait_ms(1000);
    }
}
