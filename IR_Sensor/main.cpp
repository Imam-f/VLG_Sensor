#include "mbed.h"
#include "SHARPIR.h"
 
SHARPIR Sensor(PA_4); //the output of the sharpIR sensor is connected to the MBEDs pin 10.
Serial pc(USBTX,USBRX,9600);
int main() {
    float DistanceCM;
    while (1) { //creates an eternal loop
        DistanceCM=Sensor.cm();
        wait_ms(500); //wait 20 ms between each readout
        
        // Cetak data

        pc.printf("IR : \n\r");
        pc.printf("%f\n\r",DistanceCM);
        pc.printf("_________________\n\r");
        wait_ms(500);
    }
}