#include <reg51.h>

sbit red    = P2^0;
sbit yellow = P2^1;
sbit green  = P2^2;

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
    red = 0; yellow = 0; green = 0;  

    while(1) {
        red = 1; yellow = 0; green = 0;  
        delay50ms();  

        red = 0; yellow = 1; green = 0;   
        delay50ms();  

        red = 0; yellow = 0; green = 1;   
        delay50ms(); 
    }
}

