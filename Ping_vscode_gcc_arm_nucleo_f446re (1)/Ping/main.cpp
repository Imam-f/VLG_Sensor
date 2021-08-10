// Library
# include "mbed.h"
# include "Ping.h"


// Pin Declaration

Ping Pingerfm(PC_8);
Ping Pingerbaru(PA_15);
Ping Pingerfr(PA_14);
Ping Pingerl(PD_2);

Ping Pingerr(PC_4);
Ping Pingerbr(PB_2);
Ping Pingerbl(PA_11);
Ping Pingerb(PB_1);


AnalogIn UV1(PC_0);
AnalogIn UV2(PC_1);
AnalogIn UV3(PB_0);

// Variable storage

int pingfm;
int pingval;
int pingfr;
int pingl;

int pingr;
int pingbr;
int pingbl;
int pingb;


float uviolet[3];

// MAIN
int main()
{

    while(1) {
        // Kirim sinyal

        Pingerfm.Send();
        wait_ms(30);
        pingfm = Pingerfm.Read_cm();

        Pingerbaru.Send();
        wait_ms(30);
        pingval  = Pingerbaru.Read_cm();

        Pingerfr.Send();
        wait_ms(30);
        pingfr = Pingerfr.Read_cm();

        //////////////////////////////////////////////

        Pingerl.Send();
        wait_ms(30);
        pingl  = Pingerl.Read_cm();

        Pingerr.Send();
        wait_ms(30);
        pingr  = Pingerr.Read_cm();

        Pingerbr.Send();
        wait_ms(30);
        pingbr = Pingerbr.Read_cm();

        ////////////////////////////////////////////

        Pingerbl.Send();
        wait_ms(30);
        pingbl = Pingerbl.Read_cm();

        Pingerb.Send();
        wait_ms(30);
        pingb  = Pingerb.Read_cm();
        
        wait_ms(200);

        ////////////////////////////////

        uviolet[0] = UV1.read();
        uviolet[1] = UV2.read();
        uviolet[2] = UV3.read();
        
        
        // Cetak data

        printf("ping : \n\r");
//        printf("Ping %d",pingfm);
        printf("%d__%d__%d__%d\n\r%d__%d__%d__%d\n\r",
                  pingfm, pingval, pingfr,
                  pingl, pingr, pingbr, pingbl, pingb);
        printf("_______________________________________________\n\r");
        
        printf("UV : \n\r");
        printf("%f__%f__%f\n\r",
                  uviolet[0], uviolet[1], uviolet[2]);
        printf("_______________________________________________\n\r");
        
    }
}
