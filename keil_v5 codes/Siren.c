#include<reg51.h>

// Use Port 2 for better reliability
sbit BUZZER = P2^0;    // Buzzer on P2.0
sbit LED = P3^0;       // LED on P2.1

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
    generate_tone(800, 300);  // High tone
    generate_tone(400, 300);  // Low tone
    delay_ms(200);            // Pause
}

// Simple beep for testing
void test_beep()
{
    generate_tone(1000, 200); // 1kHz beep
    delay_ms(300);            // Pause
}

void main()
{
    // Initialize Port 2 as output
    P2 = 0x00;
    
    while(1)
    {
        // Test with simple beep first
        test_beep();
        
        // Then try police siren
        police_siren();
        
        // Then ambulance siren
        ambulance_siren();
    }
}