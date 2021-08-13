#include "mbed.h"

DigitalOut relay(PB_5);

int main() {
    while (1) {
        relay = 0;
        printf("Relay %d is now off %d\r\n", relay.is_connected(),relay.read());
        wait_ms(1000);
        
        relay = 1;
        printf("Relay %d is now on %d\r\n", relay.is_connected(), relay.read());
        wait_ms(1000);
    }
}
