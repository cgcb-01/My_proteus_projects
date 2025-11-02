#include<reg51.h>

sbit ADC_RD = P2^5;
sbit ADC_WR = P2^6;
sbit ADC_INTR = P2^7;
sbit LCD_RS = P2^2;
sbit LCD_EN = P2^1;

// Add delay function
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

void lcd_cmd(unsigned char cmd)
{
    P3 = cmd;
    LCD_RS = 0;
    LCD_EN = 1;
    delay_ms(2);    // Added delay
    LCD_EN = 0;
    delay_ms(2);    // Added delay
}

void lcd_data(unsigned char dat)
{
    P3 = dat;
    LCD_RS = 1;
    LCD_EN = 1;
    delay_ms(2);    // Added delay
    LCD_EN = 0;
    delay_ms(2);    // Added delay
}

void lcd_string(char *s)
{
    while(*s) lcd_data(*s++);
}

void lcd_init()
{
    delay_ms(20);   // LCD power-up delay
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
}

unsigned char read_adc()
{
    unsigned char value;
    
    // Start conversion sequence
    ADC_WR = 0;
    delay_ms(1);    // Wait for setup
    ADC_WR = 1;     // Rising edge starts conversion
    delay_ms(1);
    
    // Wait for conversion to complete (INTR goes LOW)
    while(ADC_INTR == 1);  // FIXED: Wait while INTR is HIGH
    
    // Read data
    ADC_RD = 0;
    delay_ms(1);
    value = P1;     // Read ADC value
    ADC_RD = 1;
    
    return value;
}

void main()
{
    unsigned char adc_val;
    
    // Initialize ports
    P1 = 0xFF;      // Make Port 1 input for ADC
    
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("ADC Value:");
    
    while(1)
    {
        adc_val = read_adc();
        
        lcd_cmd(0xC0);        // Second line
        
        // Display digital value
        lcd_data('D');
        lcd_data(':');
        lcd_data(adc_val/100 + '0');
        lcd_data((adc_val/10)%10 + '0');
        lcd_data(adc_val%10 + '0');
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(' ');
        lcd_data(' ');
        
        delay_ms(200);  // Refresh rate
    }
}