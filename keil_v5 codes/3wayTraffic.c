#include <reg51.h>

// Traffic Light 1
sbit red1    = P2^0;
sbit yellow1 = P2^1;
sbit green1  = P2^2;

// Traffic Light 2
sbit red2    = P2^3;
sbit yellow2 = P2^4;
sbit green2  = P2^5;

// Traffic Light 3
sbit red3    = P2^6;
sbit yellow3 = P2^7;
sbit green3  = P3^0;   // using Port3 pin

// 10s delay using Timer0
void delay10s() {
    unsigned int i;
    TMOD = 0x01; // Timer0 Mode1 (16-bit)
    for(i = 0; i < 200; i++) {   // 200 * 50ms = 10s
        TH0 = 0x4C;   
        TL0 = 0x00;
        TR0 = 1;    
        while(TF0 == 0); 
        TR0 = 0;     
        TF0 = 0;     
    }
}

// make all yellow ON
void allYellow() {
    red1=0; green1=0; yellow1=1;
    red2=0; green2=0; yellow2=1;
    red3=0; green3=0; yellow3=1;
    delay10s();   // all yellow for 10s
}

void main() {
    // all off initially
    red1=yellow1=green1=0;
    red2=yellow2=green2=0;
    red3=yellow3=green3=0;

    while(1) {
        // ---- Light 1 Green, others Red ----
        red1=0; yellow1=0; green1=1;
        red2=1; yellow2=0; green2=0;
        red3=1; yellow3=0; green3=0;
        delay10s();

        allYellow();   // <-- ALL yellow phase

        // ---- Light 2 Green, others Red ----
        red1=1; yellow1=0; green1=0;
        red2=0; yellow2=0; green2=1;
        red3=1; yellow3=0; green3=0;
        delay10s();

        allYellow();   // <-- ALL yellow phase

        // ---- Light 3 Green, others Red ----
        red1=1; yellow1=0; green1=0;
        red2=1; yellow2=0; green2=0;
        red3=0; yellow3=0; green3=1;
        delay10s();

        allYellow();   // <-- ALL yellow phase
    }
}
