#include "mbed.h"
#include "AMG8833.h"
#include "Ping.h"

/*
 *
 * 2x Line     ////////////////////////////////
-- PH_1, PH_0
 * 
 * 1x Relay    //////////////////////////////
-- PA_12
 * 
 * Button : SIG GND 1        //////////////////////////
 * 
 * 
 * 
 * 8x Ping    ///////////////////////////
-- PC_4, PB_2,
-- PD_2 PB_1, PA_11
-- PA_14, PA_15, PC_8
 * 
 * 5x IR     ////////////////////////////////
-- PC_0, PC_1, PB_0, 
-- PA_4, PC_2
 * 
 *
 * 
 * LCD : GND VCC SDA SCL       ////////////////////////
 * 
 * AMG : VCC GND SCL SDA X X   ////////////////////////
 * 
 * Color /////////////////////////////
 * 
 * Gripper //////////////////////
 * 
 */

////// Digital ////////////////////////

DigitalIn   Line1(PB_5);    // 
DigitalIn   Line2(PB_5);    // 
DigitalIn  Button(PB_5);    // 
DigitalOut  Relay(PB_5);    // OK

int digital[4];


//// AMG /////////////////////////////// OK

Adafruit_AMG88xx amg(PB_3, PB_10);
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];


///// LCD ////////////////////////////// OK

I2C i2c_lcd(PB_9,PB_8); // SDA, SCL
TextLCD_I2C lcd(&i2c_lcd, 0x27<<1, TextLCD::LCD16x2);  // I2C bus, PCF8574 Slaveaddress, LCD Type


////// Ping ////////////////////////////

Ping Pinger1(PC_8 );
Ping Pinger2(PA_15);
Ping Pinger3(PA_14);
Ping Pinger4(PD_2 );

Ping Pinger5(PC_8 );
Ping Pinger6(PA_15);
Ping Pinger7(PA_14);
Ping Pinger8(PD_2 );


int ping1; int ping2;
int ping3; int ping4;
int ping5; int ping6;
int ping7; int ping8;


////// IR ////////////////////////////////////

AnalogIn UV1(PC_0);
AnalogIn UV2(PC_0);
AnalogIn UV3(PC_0);
AnalogIn UV4(PC_0);
AnalogIn UV5(PC_0);

float uviolet[5];


////// Color ///////////////////////////////// OK

InterruptIn  in(PA_0 );
DigitalOut   s0(PA_13), s1(PA_14); // s2(p7), s3(p8)
BusOut setColor(PA_15,     PC_15); //(LSB pin,..., MSB pin): (s3, s2). Red: 0, Blue: 1, Clear: 2, Green: 3.
Timer t;

float period = 0; // This is the period between interrupts in microseconds
float freq = 0;
float f_red = 0;
int n;
int color; // Color

void print();
void time();


///// Gripper /////////////////////////////// OK

DigitalOut myled(LED1);
Servo  servoGrab(PA_1);
Servo  servoTurn(PA_0);

void grabBoneka();
void releaseBoneka();
void turnBoneka();
void turnBonekaBack();
void liftBoneka();
void downBoneka();
    


///// Main Test /////////////////////////////

int main() {

    // LCD

    printf("LCD Test. Columns=%d, Rows=%d\n\r", lcd.columns(), lcd.rows());

    lcd.setCursor(TextLCD::CurOff_BlkOn);
 
    lcd.setMode(TextLCD::DispOn);
    lcd.setBacklight(TextLCD::LightOn);
    lcd.cls();
    lcd.printf("Sukses");  


    // AMG

    wait_ms(100);
    amg.begin();
    

    // Color

    in.mode(PullDown); // Set the pin to Pull Down mode.
    wait_ms(1000);
    n = 0;
    color = 0;
    setColor = color;

    s0 = 0; s1 = 1;         // Frequency 2% = 12 kHz full-scale.

    in.rise(&time);         // Set up the interrupt for rising edge
    t.start();              // Start the timer


    // Servo
    
    servoGrab.calibrate(0.00125,45.0);
    servoTurn.calibrate(0.00125,45.0);
    
    // Posisi Awal Servo
    servoGrab = 0;
    servoTurn = 0.5;
    wait_ms(1000);



    while (1) {

        // Digital

        digital[0] = line1.read();
        digital[1] = line2.read();
        digital[2] = button.read();

        printf("Line : \n\r");
        printf("%d__%d__%d\n\r",
                  digital[0], digital[1], digital[2]);
        printf("_______________________________________________\n\r");

        
        // Ping

        Pinger1.Send();
        wait_ms(30);
        ping1 = Pinger1.Read_cm();

        Pinger2.Send();
        wait_ms(30);
        ping2 = Pinger2.Read_cm();
        
        Pinger3.Send();
        wait_ms(30);
        ping3 = Pinger3.Read_cm();
        
        Pinger4.Send();
        wait_ms(30);
        ping4 = Pinger4.Read_cm();
        
        Pinger5.Send();
        wait_ms(30);
        ping5 = Pinger5.Read_cm();
        
        Pinger6.Send();
        wait_ms(30);
        ping6 = Pinger6.Read_cm();
        
        Pinger7.Send();
        wait_ms(30);
        ping7 = Pinger7.Read_cm();
        
        Pinger8.Send();
        wait_ms(30);
        ping8 = Pinger8.Read_cm();

        printf("ping : \n\r");
        printf("%d__%d__%d__%d\n\r%d__%d__%d__%d\n\r",
                  ping1, ping2, ping3, ping4,
                  ping5, ping6, ping7, ping8);
        printf("_______________________________________________\n\r");


        // IR

        uviolet[0] = UV1.read();
        uviolet[1] = UV2.read();
        uviolet[2] = UV3.read();
        uviolet[3] = UV4.read();
        uviolet[4] = UV5.read();
        
        printf("UV : \n\r");
        printf("%f__%f__%f__%f__%f\n\r",
                  uviolet[0], uviolet[1], uviolet[2],
                  uviolet[3], uviolet[4]);
        printf("_______________________________________________\n\r");


        // AMG

        wait_ms(100);

        //read all the pixels
        printf("rd1");
        amg.readPixels(pixels);
        printf("-rd2\r\n");

        printf("Reading . . . \n\r");
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                // if(pixels[(i*8) + j] > 40){
                //     printf("*  ");
                // }
                // else {
                //     printf("|  ");
                // }
                printf("%7.2f    ", pixels[i*8 + j]);
            }
            printf("\n\r");
        }
        printf("\n\r");
        printf("\n\r");


        // Servo

        grabBoneka();
        printf("Tutup\r\n");
        wait_ms(500);
        
        liftBoneka();
        printf("Angkat\n\r");
        wait_ms(2000);
        
        downBoneka();
        printf("Turun!\n\r");
        wait_ms(500);
        
        releaseBoneka();
        printf("Buka!\n\r");
        wait_ms(1000);


        // Relay
        
        relay = 0;
        printf("Relay %d is now off %d\r\n", relay.is_connected(), relay.read());
        wait_ms(1000);
        
        relay = 1;
        printf("Relay %d is now on %d\r\n", relay.is_connected(), relay.read());
        wait_ms(500);

    }
}
 
 

void grabBoneka() {
    for(int i=0; i<25; i++) {
        servoGrab = i/100.0;
        wait_ms(10);
    }
}
void releaseBoneka() {
    for(int i=25; i>0; i--) {
        servoGrab = i/100.0;
        wait_ms(10);
    }
}
void turnBoneka() {
    for(int i=50; i>10; i--) {
        servoTurn = i/100.0;
        wait_ms(10);
    }
}
void turnBonekaBack() {
    for(int i=10; i<50; i++) {
        servoTurn = i/100.0;
        wait_ms(10);
    }
}
void liftBoneka() {
    for(int i=80; i>50; i--) {
        servoTurn = i/100.0;
        wait_ms(10);
    }
}
void downBoneka() {
    for(int i=50; i<80; i++) {
        servoTurn = i/100.0;
        wait_ms(10);
    }
}
    


void print() {  // Print to PC
    switch (color) {
        case 0:
            f_red = freq;
            printf(" Red: \t\t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 1:
            printf(" Blue: \t\t%.2f Hz, \t%.2f us\r\n", freq, period);
            break;
        case 2:
            printf(" Clear: \t%.2f Hz, \t%.2f us\r\n", freq, period);
            printf("rasio = %f\n\r", f_red/freq);
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
        color = color == 0 ? 2 : 0 ;
        setColor = color;
        
        wait(0.5);
        t.reset(); // Reset timer and wait for next interrupt
    }
    n++;
}

