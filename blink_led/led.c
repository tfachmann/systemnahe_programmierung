#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()

const int x = 20;
int main(void)
{
    DDRB = 0xFF;                       // initialize port B
    while(1)
    {
        // LED on
        //PORTB = 0b00010000;            // PB4 = High = Vcc
        //PORTB = 0x10;
        //PORTB = 16;
        
        //PORTB = 1 << 4;
        //PORTB = 1 << PINB4;
        
        //PORTB |= (1 << PINB5);
        //PORTB |= (1 << PINB4);
        //PORTB |= (1 << PINB5) | (1 << PINB4);
        //PORTB = 16+32;
        //PORTB = 0b00110000;
        //PORTB = 0x30;
        
        PORTB = ~PORTB;
        PORTB &= (1 << PINB4);
        _delay_ms(250);                // wait 500 milliseconds

        //LED off
        //PORTB = 0b00000000;            // PB0 = Low = 0v
        PORTB = 0x00;
        _delay_ms(250);                // wait 500 milliseconds
    }
}
