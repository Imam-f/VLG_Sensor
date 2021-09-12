#include "mbed.h"
#include "Servo.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut myled(LED1);
Servo servoGrab(PB_3);
Servo servoTurn(PA_10);

void grabBoneka() {
    for(int i=0; i<25; i++) {
        servoGrab = i/100.0;
        wait(0.01);
    }
}
void releaseBoneka() {
    for(int i=25; i>0; i--) {
        servoGrab = i/100.0;
        wait(0.01);
    }
}
void turnBoneka() {
    for(int i=50; i>10; i--) {
        servoTurn = i/100.0;
        wait(0.01);
    }
}
void turnBonekaBack() {
    for(int i=10; i<50; i++) {
        servoTurn = i/100.0;
        wait(0.01);
    }
}
void liftBoneka() {
    for(int i=80; i>50; i--) {
        servoTurn = i/100.0;
        wait(0.01);
    }
}
void downBoneka() {
    for(int i=50; i<80; i++) {
        servoTurn = i/100.0;
        wait(0.01);
    }
}
    
int main() {
    pc.printf("Hello World !\n");
    
    // Kalibrasi Range Servo (idealnya bisa dari 0-180 derajat), harus di tuning manual
    servoGrab.calibrate(0.00125,45.0);
    servoTurn.calibrate(0.00125,45.0);
    
    // Posisi Awal Servo
    servoGrab = 0;
    servoTurn = 0.5;
    wait_ms(1000);
    
    while(1) {
            // Basic Moveset: Grab Boneka, angkat, turunin, lepas boneka
        grabBoneka();
        pc.printf("Tutup\r\n");
        wait_ms(500);
        
        liftBoneka();
        pc.printf("Angkat\n\r");
        wait_ms(2000);
        
        downBoneka();
        pc.printf("Turun!\n\r");
        wait_ms(500);
        
        releaseBoneka();
        pc.printf("Buka!\n\r");
        wait_ms(1000);
    }
}
