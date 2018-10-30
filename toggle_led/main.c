/*
 * toggle_led.c
 *
 * Created: 13.10.2018 13:11:52
 * Author : Dominik
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0xFF;
    PORTB = 0x00;
	DDRD = 0x00;
	PORTD = 0xFF;
	
    while (1) 
    {
		if(!(PIND & PIND2))
			PORTB = 0;
		else
			PORTB = 0xFF;
		
    }
}

