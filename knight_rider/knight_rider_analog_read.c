#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include <stdio.h>

const int var = 150;
int reading;

int read_analog(){
    reading = 0;
    ADCSRA |= (1 << ADSC);
    return reading;
}

void delay_custom(int multiplier){
    for(int i = 0; i < multiplier; ++i){
        _delay_ms(10);
    }
}
//Function to read an ADC Channel (once the ADC is setup)
uint8_t ADC_read(uint8_t channel)
{
  ADMUX &= (1<<REFS1) | (1<<REFS0);     // Clear the ADC Multiplexer
  ADMUX |= channel;                      // Set the ADC multiplexer
  ADCSRA |= ADSC;               // Start an ADC conversion
  while(ADCSRA & (1<<ADSC));    // Wait until conversion is complete
  return (ADCH);                // Return the ADC high register value
}

int main(void)
{
    DDRB = 0xFF;                       // initialize port B

    // Setting up the ADC
    ADMUX = (1<<REFS1);     // Use internal 1.1V reference voltage, multiplexer = 0
    ADCSRA = 
        (1<<ADPS1) |        // Prescaler = 4: F_ADC = F_cpu / prescaler
        (1<<ADEN);          // Enable the ADC
    ADCSRB = (1<<ADLAR);    // Left Adjust Result for 8 bit resolution

    // Taking a measurement
    ADCSRA |= ADSC;               // Start an ADC conversion
    while(ADCSRA & (1<<ADSC));    // Wait until conversion is complete
    ADC = ADCH;             // Read the ADC high register

    // Enabling the ISR
    ADCSRA |= (1<<ADIE);          // Enable ADC Interrupt


    while(1)
    {
        int reading_str = ADC_read(0);
        // LED on
        for(int i = 0; i < 6; ++i){
            PORTB |= (1 << i);
            /*_delay_ms(var);                // wait 500 milliseconds*/
            delay_custom(reading_str);
            PORTB &= ~(1 << i);
        }
        for(int i = 4; i > 0; --i){
            PORTB |= (1 << i);
            /*_delay_ms(var);                // wait 500 milliseconds*/
            delay_custom(reading_str);
            PORTB &= ~(1 << i);
        }
    }
}
