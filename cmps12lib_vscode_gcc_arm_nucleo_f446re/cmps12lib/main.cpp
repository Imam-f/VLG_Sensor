#include "mbed.h"
#include "CMPS_KRAI.h"

CMPS_KRAI cmps12(PB_4, PA_8, 0xC0);

int main() {
    cmps12.eraseProfile();
    while (1) {
        int deg = cmps12.readBearing();
        int status = cmps12.state(SYSTEM_STATE);
        printf("%d %d\n", deg, status);
        wait_ms(200);
        printf("\033[2J\033[H");
    }
}