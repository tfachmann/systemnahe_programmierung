/*
* serial_toPc.c
*
* Created: 03.11.2018 11:34:35
* Author : Dominik
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Declaration of our functions
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);
void enable_read_analog();

char String[]="Hello world!!";    //String[] is in fact an array but when we put the text between the " " symbols the compiler threats it as a String and automatically puts the null termination character in the end of the text
volatile uint8_t ADCLow = 0; //variable to read analog low register
volatile uint8_t ADCHigh = 0; // " high
uint16_t ADCSum = 0;
char toSend[10]; 
int main(void){
	USART_init();        //Call the USART initialization code
	
	while(1){
        
		ADCSum = (ADCHigh << 8) | ADCLow;
		USART_putstring(itoa(ADCSum, toSend,10));
	}
	
	return 0;
}

void USART_init(void){
	
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8); //set baud prescaler
	UBRR0L = (uint8_t)(BAUD_PRESCALLER); //same
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //enable send and receive
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01); // set 8-bit message
	
	UCSR0B |= (1 << RXCIE0);                   // Enable the receiver interrupt
	
	enable_read_analog();
	
	sei();
}

unsigned char USART_receive(void){
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void USART_send( unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0))); // wait till buffer is empty
	UDR0 = data;
	
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00){
		USART_send(*StringPtr);
	StringPtr++;}
	USART_send('\n');
}

ISR (USART_RX_vect){
	USART_send(UDR0);
}

//code from previous project
void enable_read_analog(){
	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion
}

//interrupt for reading analog signal
ISR(ADC_vect)
{
	ADCLow= ADCL;
	ADCHigh = ADCH;     
	   
	// only need to read the high value for 8 bit , low and high for 10 bit
	// REMEMBER: once ADCH is read the ADC will update
	
	// if you need the value of ADCH in multiple spots, read it into a register
	// and use the register and not the ADCH

}