#include "mbed.h"
#include "AMG8833.h"

Adafruit_AMG88xx amg( PB_3, PB_10);
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];


int main() {
    // AMG
     wait(0.01);
     printf("Setup");
 
    while (1) {

        amg.begin();
        wait(1) ;
        //read all the pixels
        amg.readPixels(pixels);
        
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if(pixels[(i*8) + j] > 40){
                    printf("*  ");
                }
                else {
                    printf("|  ");
                }
            }
            printf("\n\r");
        }
        printf("\n\r");
        printf("\n\r");

    }
}
 
 
