/*
 * interrupts.c
 *
 * Created: 13.10.2018 13:58:52
 * Author : Dominik
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect){PORTB = 0x00;} //disables led
ISR(INT1_vect){PORTB = 0xFF;} //enables led


int main(void)
{
    DDRB = 0xFF;
	PORTB = 0xFF;
	
	DDRD &= ~(1<<DDD2); //reset pin 2
	PORTD |= (1<<PORTD2); //pull up pin 2
	
	DDRD &= ~(1<<DDD3); // same like 2
	PORTD |= (1<< PORTD3); // same like 2
	
	EICRA |=(1<<ISC01); //see table for isc settings => triggering on moving towards low
	EICRA |=(1<<ISC11); // look above
	EIMSK |= (1<<INT0); //turns on
	EIMSK |=(1<<INT1); //turns on
	
	sei();// enable interrupts system-wide
	
    while (1) 
    {
	
		
    }
}

