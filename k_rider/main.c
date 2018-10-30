/*
* k_raider.c
*
* Created: 30.10.2018 13:43:13
* Author : Dominik
*/
#define F_CPU 16000000UL
#define dlay 100
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void my_delay();

int speed = 1;

ISR(INT0_vect)
{ if(speed == 3)
	{
		speed = 1;
		} else{
		speed++;
	}
}



int main(void)
{
	DDRB=0xFF;
	PORTB=0;
	
	DDRD = 0;
	PORTD |= (1<<PORTD2);
	
	EICRA |=(1<<ISC01); //see table for isc settings => triggering on moving towards low
	EICRA |=(1<<ISC11); // look above
	
	EIMSK |= (1<<INT0); //turns on
	
	sei();
	
	
	while (1)
	{for(int i = 0; i<6; i++)
		{
			PORTB |= 1<<i;
			my_delay();
			PORTB &= ~(1<<i);
		}
		
		for(int i = 4; i>0; i--)
		{
			PORTB |= 1<<i;
			my_delay();
			PORTB &= ~(1<<i);
		}
	}
}

void my_delay()
{
	switch(speed){
		case 1:
		_delay_ms(50);
		break;
		case 2:
		_delay_ms(500);
		break;
		case 3:
		_delay_ms(1000);
		break;
		default:
		break;
	}
}


