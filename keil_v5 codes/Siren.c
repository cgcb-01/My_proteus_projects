#include<reg51.h>

// Pin Definitions
sbit BUZZER = P2^0;    // Buzzer on P2.0
sbit LED = P3^0;       // LED on P3.0

// LCD Control Pins
sbit LCD_RS = P3^6;
sbit LCD_EN = P3^7;

// FUNCTION PROTOTYPES - ADD THESE
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_string(char *s);
void lcd_clear();
void lcd_init();
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);
void generate_tone(unsigned int frequency, unsigned int duration_ms);
void police_siren();
void ambulance_siren();
void fire_siren();
void test_beep();
void display_siren_type(char *siren_name);

// LCD Functions
void lcd_cmd(unsigned char cmd)
{
    P1 = cmd;          // Command on Port 1
    LCD_RS = 0;        // Command mode
    LCD_EN = 1;        // Enable pulse
    delay_ms(2);
    LCD_EN = 0;
    delay_ms(2);
}

void lcd_data(unsigned char dat)
{
    P1 = dat;          // Data on Port 1
    LCD_RS = 1;        // Data mode
    LCD_EN = 1;        // Enable pulse
    delay_ms(2);
    LCD_EN = 0;
    delay_ms(2);
}

void lcd_string(char *s)
{
    while(*s) lcd_data(*s++);
}

void lcd_clear()
{
    lcd_cmd(0x01);     // Clear display
    delay_ms(2);
}

void lcd_init()
{
    delay_ms(20);      // LCD power-up delay
    lcd_cmd(0x38);     // 8-bit, 2-line, 5x7
    lcd_cmd(0x0C);     // Display ON, cursor OFF
    lcd_clear();       // Clear display
    lcd_cmd(0x06);     // Entry mode
}

// Display siren type on LCD
void display_siren_type(char *siren_name)
{
    lcd_cmd(0x80);     // First line
    lcd_string("Siren Type:      ");
    lcd_cmd(0xC0);     // Second line
    lcd_string(siren_name);
}

// Accurate delay function
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1275; j++);
}

// Microsecond delay for precise PWM
void delay_us(unsigned int us)
{
    while(us--);
}

// Generate tone with specific frequency and duration
void generate_tone(unsigned int frequency, unsigned int duration_ms)
{
    unsigned long i, cycles;
    unsigned int half_period_us;
    
    // Calculate half period in microseconds
    half_period_us = 500000 / frequency;
    
    // Calculate number of cycles for desired duration
    cycles = ((unsigned long)duration_ms * 1000) / (half_period_us * 2);
    
    // Generate the PWM signal
    for(i=0; i<cycles; i++)
    {
        BUZZER = 1;    // Buzzer ON
        LED = 1;       // LED ON
        delay_us(half_period_us);
        
        BUZZER = 0;    // Buzzer OFF
        LED = 0;       // LED OFF
        delay_us(half_period_us);
    }
}

// Police siren effect
void police_siren()
{
    unsigned int freq;
    lcd_cmd(0x01);
    display_siren_type("POLICE SIREN    ");
    
    // Siren UP - increasing frequency
    for(freq=400; freq<=1200; freq+=20)
    {
        generate_tone(freq, 15);
    }
    
    // Siren DOWN - decreasing frequency
    for(freq=1200; freq>=400; freq-=20)
    {
        generate_tone(freq, 15);
    }
}

// Ambulance siren effect
void ambulance_siren()
{
	lcd_cmd(0x01);
    display_siren_type("AMBULANCE       ");
    
    generate_tone(800, 300);  // High tone
    generate_tone(400, 300);  // Low tone
    delay_ms(2);            // Pause
}

// Fire engine siren effect
void fire_siren()
{
    unsigned int freq;
    
    display_siren_type("FIRE ENGINE     ");
    
    // Fast sweep
    for(freq=500; freq<=2000; freq+=50)
    {
        generate_tone(freq, 8);
    }
    for(freq=2000; freq>=500; freq-=50)
    {
        generate_tone(freq, 8);
    }
}

// Simple beep for testing
void test_beep()
{
    display_siren_type("TEST BEEP       ");
    generate_tone(1000, 200); // 1kHz beep
    delay_ms(300);            // Pause
}

void main()
{
    // Initialize ports
    P2 = 0x00;  // Port 2 as output (Buzzer)
    P3 = 0x00;  // Port 3 as output (LED & LCD control)
    P1 = 0x00;  // Port 1 as output (LCD data)
    
    // Initialize LCD
    lcd_init();
    
    // Display welcome message
    lcd_cmd(0x80);
    lcd_string("SIREN SYSTEM");
    lcd_cmd(0xC0);
    lcd_string("INITIALIZED  ");
    delay_ms(1000);
    
    while(1)
    {
        // Test with simple beep first
        test_beep();
        delay_ms(5);
        
        // Police siren
        police_siren();
        delay_ms(5);
        
        // Ambulance siren
        ambulance_siren();
        delay_ms(5);
        
        // Fire engine siren
        fire_siren();
        delay_ms(5);
    }
}