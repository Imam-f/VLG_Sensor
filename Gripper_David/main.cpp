#include "mbed.h"
#include "Servo.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------


#define LEFTIR PC_9
#define RIGHTIR PB_8
Serial pc(SERIAL_TX, SERIAL_RX);
DigitalOut myled(LED1);
Servo servoGrab(PA_9);
Servo servoTurn(PA_10);
DigitalIn IRGRIPPERLEFT(PH_0);
DigitalIn IRGRIPPERRIGHT(PH_1);
void grabBoneka()
{
    for(int i=0; i<25; i++) {
        servoGrab = i/100.0;
        wait(0.01);
    }
}

void releaseBoneka()
{

    for(int i=25; i>0; i--) {
        servoGrab = i/100.0;
        wait(0.01);
    }
}
void turnBoneka()
{
    for(int i=50; i>10; i--) {
        servoTurn = i/100.0;
        wait(0.01);
    }
}
void turnBonekaBack()
{
    for(int i=10; i<50; i++) {
        servoTurn = i/100.0;
        wait(0.01);
    }

}
void liftBoneka()
{

    for(int i=80; i>50; i--) {
        servoTurn = i/100.0;
        wait(0.01);
    }
}
void downBoneka()
{
    for(int i=50; i<80; i++) {
        servoTurn = i/100.0;
        wait(0.01);
    }

}

int main()
{
    pc.printf("Hello World !\n");
    // Kalibrasi Range Servo (idealnya bisa dari 0-180 derajat), harus di tuning manual
    servoGrab.calibrate(0.00125,45.0);
    servoTurn.calibrate(0.00125,45.0);
    // Posisi Awal Servo
    servoGrab = 0;
    servoTurn = 0.8;
    wait(1);
    int left=0;
    int right=0;
    while(1) {
        // Basic Moveset: Grab Boneka, angkat, turunin, lepas boneka
        left = !IRGRIPPERLEFT;
        right = !IRGRIPPERRIGHT;
        pc.printf("Condition R:%d L:%d \n",right,left);
//
        if (left && right) {
            pc.printf("Sudah didepan ! Start Gripper\n");
            wait(1);
            grabBoneka();
            wait(0.5);
            liftBoneka();
            wait(2);
            downBoneka();
            wait(0.5);
            releaseBoneka();
            wait(1);
        } 
        else if(left) pc.printf("Ke kanan lagi\n");
        else if (right) pc.printf("ke kiri lagi\n");

        wait(0.1);


    }

}
