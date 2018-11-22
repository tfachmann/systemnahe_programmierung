/*
 * pwm_dim_led.c
 *
 * Created: 03.11.2018 09:52:17
 * Author : Dominik
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
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
    
    while (1) 
    {
		for(int i = 0; i<256; i++){
			OCR0A = i;
			_delay_ms(10);
		}
			
			for(int i = 255; i>=0; i--){
				OCR0A = i;
				_delay_ms(10);
			}
			
    }
}

