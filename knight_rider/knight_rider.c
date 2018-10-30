#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()

void delay_custom(int multiplier){
    for(int i = 0; i < multiplier; ++i){
        _delay_ms(10);
    }
}

int main(void)
{
    DDRB = 0xFF;                       // initialize port B

    while(1)
    {
        uint8_t delay_multiplier = 10;
        // LED on
        for(int i = 0; i < 6; ++i){
            PORTB |= (1 << i);
            /*_delay_ms(var);                // wait 500 milliseconds*/
            delay_custom(delay_multiplier);
            PORTB &= ~(1 << i);
        }
        for(int i = 4; i > 0; --i){
            PORTB |= (1 << i);
            /*_delay_ms(var);                // wait 500 milliseconds*/
            delay_custom(delay_multiplier);
            PORTB &= ~(1 << i);
        }
    }
}
