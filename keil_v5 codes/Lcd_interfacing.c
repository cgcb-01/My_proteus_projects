#include <reg51.h>
sbit RS = P2^0;
sbit RW = P2^1;
sbit E  = P2^2;
sbit d0 = P3^0;
sbit d1 = P3^1;
sbit d2 = P3^2;
sbit d3 = P3^3;
sbit d4 = P3^4;
sbit d5 = P3^5;
sbit d6 = P3^6;
sbit d7 = P3^7;
void delay(unsigned int t) {
    unsigned int i, j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_pulse() {
    E = 1;
    delay(1);
    E = 0;
}

void lcd_cmd(unsigned char cmd) {
    RS = 0; RW = 0;
    P3 = cmd;   
    lcd_pulse();
    delay(2);
}

void lcd_data(unsigned char dat) {
    RS = 1; RW = 0;
    P3 = dat;    
    lcd_pulse();
    delay(2);
}

void lcd_init() {
    lcd_cmd(0x38); 
    lcd_cmd(0x0C); 
    lcd_cmd(0x06);
    lcd_cmd(0x01); 
}

void lcd_string(char *str) {
    while(*str) {
        lcd_data(*str++);
        delay(50);  
    }
}

void main() {
    lcd_init();
    lcd_string("HELLO WORLD");
    while(1);
}