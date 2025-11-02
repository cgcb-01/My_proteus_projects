#include <reg51.h>

sbit red1    = P2^0;
sbit yellow1 = P2^1;
sbit green1  = P2^2;
sbit red2    = P2^3;
sbit yellow2 = P2^4;
sbit green2  = P2^5;
void delay50ms() {
    unsigned int i;

    TMOD = 0x01;    
    for(i = 0; i < 200; i++) {  
        TH0 = 0x4C;   
        TL0 = 0x00;
        TR0 = 1;    
        while(TF0 == 0); 
        TR0 = 0;     
        TF0 = 0;     
    }
}

void main() {
    red1 = 0; yellow1 = 0; green1 = 0;red2 = 0; yellow2 = 0; green2 = 0;  

    while(1) {
        red1 = 1; yellow1 = 0; green1 = 0;red2 = 0; yellow2 = 0; green2 = 1;
        delay50ms();  

        red1 = 0; yellow1 = 0; green1 = 1;red2 = 1; yellow2 = 0; green2 = 0;   
        delay50ms();  

        red1 = 0; yellow1 = 1; green1 = 0;red2 = 0; yellow2 = 1; green2 = 0;   
        delay50ms(); 
    }
}

