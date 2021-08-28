#include "mbed.h"
#include "AMG8833.h"

Adafruit_AMG88xx amg( PB_3, PB_10);
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];


int main() {
    // AMG
    wait_ms(100);
    printf("Setup");
    amg.begin();
    printf("Begin");

    while (1) {

        wait_ms(100);

        //read all the pixels
        printf("rd1");
        amg.readPixels(pixels);
        printf("-rd2\r\n");

        printf("Reading . . . \n\r");
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++) {
                if(pixels[(i*8) + j] > 40){
                    printf("*  ");
                }
                else {
                    printf("|  ");
                }
                // printf("%7.2f    ",pixels[i*8 + j]);
            }
            printf("\n\r");
        }
        printf("\n\r");
        printf("\n\r");

    }
}
 
 
