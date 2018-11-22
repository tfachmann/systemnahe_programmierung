/*
 * analog_in.c
 *
 * Created: 03.11.2018 11:03:06
 * Author : Dominik
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>       // needed for uint8_t

#include <avr/interrupt.h>


volatile uint8_t ADCvalue;    // Global variable, set to volatile if used with ISR

void enable_write_analog();

int main(void)
{
	enable_write_analog();

	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();    // Thanks N, forgot this the first time =P


	while (1)
	{
		// main loop
		
	}
}

//code from previous project dim led
void enable_write_analog(){
	DDRD |= (1 << DDD6);
	// PD6 is now an output

	OCR0A = 0;
	// set PWM for 50% duty cycle


	TCCR0A |= (1 << COM0A1);
	// set none-inverting mode

	TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1<<WGM02);
	// set fast PWM Mode

	TCCR0B |= (1 << CS01);
	// set prescaler to 8 and starts PWM
}


ISR(ADC_vect)
{
	ADCvalue= ADCH;  
	OCR0A = ADCvalue;        // only need to read the high value for 8 bit
	// REMEMBER: once ADCH is read the ADC will update
	
	// if you need the value of ADCH in multiple spots, read it into a register
	// and use the register and not the ADCH

}

