#include <reg51.h>

typedef unsigned char  u8;
typedef unsigned int   u16;

/* LCD pins (change if you wired differently) */
sbit LCD_RS = P2 ^ 0;
sbit LCD_EN = P2 ^ 2;

/* small software delay - portable */
void delay_ms(u16 ms)
{
    volatile u16 i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++) { /* tune this constant for your crystal */
            volatile u8 x = 0;
            x++;
        }
    }
}

/* tiny delay used for enable pulse */
void tiny_delay(void)
{
    volatile u16 k;
    for (k = 0; k < 200; k++); /* small loop */
}

void lcd_pulse(void)
{
    LCD_EN = 1;
    tiny_delay();
    LCD_EN = 0;
    delay_ms(1);
}

void lcd_cmd(u8 c)
{
    LCD_RS = 0;
    P3 = c;
    lcd_pulse();
    delay_ms(2);
}

void lcd_data(u8 d)
{
    LCD_RS = 1;
    P3 = d;
    lcd_pulse();
    delay_ms(1);
}

void lcd_init(void)
{
    delay_ms(20);
    lcd_cmd(0x38); /* 8-bit, 2-line */
    lcd_cmd(0x0C); /* display on, cursor off */
    lcd_cmd(0x06); /* entry mode */
    lcd_cmd(0x01); /* clear */
    delay_ms(2);
}

/* print value 0..255 on LCD (no printf) */
void lcd_print_dec(u16 v)
{
    char buf[4];
    u8 idx = 0;

    if (v > 255) v = 255;
    buf[0] = '0' + (v / 100);
    buf[1] = '0' + ((v / 10) % 10);
    buf[2] = '0' + (v % 10);
    buf[3] = 0;

    /* skip leading zeros but print at least one digit */
    if (buf[0] == '0') {
        if (buf[1] == '0') idx = 2;
        else idx = 1;
    } else idx = 0;

    while (buf[idx]) lcd_data(buf[idx++]);
}

void main(void)
{
    u16 v;
    /* make control pins known */
    LCD_RS = 0;
    LCD_EN = 0;
    P1 = 0x00; /* start DAC at 0 */
    P3 = 0x00;

    lcd_init();

    while (1) {
        for (v = 0; v < 256; v++) {
            P1 = (u8)v;            /* output to DAC */
            lcd_cmd(0x80);        /* first line pos 0 */
            lcd_print_dec(v);
            delay_ms(30);         /* ~30 ms per step - change if needed */
        }
    }
}