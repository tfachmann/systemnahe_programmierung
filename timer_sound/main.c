/*
 * timer_sound.c
 *
 * Created: 13.10.2018 15:35:41
 * Author : Dominik
 */ 

// this code sets up a timer0 for 4ms @ 16Mhz clock cycle
// an interrupt is triggered each time the interval occurs.



#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{

DDRB = 0xFF;
PORTB = 0;
	// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01);

	// Set the value that you want to count to
	OCR0A = 71;

	TIMSK0 |= (1 << OCIE0A);    //Set the ISR COMPA vect

	sei();         //enable interrupts


	TCCR0B |= (1 << CS02);
	// set prescaler to 256 and start the timer


	while (1)
	{
		//main loop
	}
}


	//event to be exicuted every xxxms here
ISR (TIMER0_COMPA_vect)  // timer0 overflow interrupt
{
	PORTB = ~PORTB;
}
