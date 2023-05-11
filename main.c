/*
 * Lab2.c
 *
 * Created: 5/27/2022 5:56:38 PM
 * Author : Abdalla
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "avr/iom328pb.h"

#define BAUD_RATE 9600
#define ubrr  F_CPU/16/BAUD_RATE-1

void USART_Init(int br)
{

	// Set the Baud rate to 9600
	UBRR0H = (br>>8);
	UBRR0L = br;

	// set the data bits to 8-bit
	UCSR0C |= ((1<<UCSZ00) | (1<<UCSZ01));
	UCSR0B &= ~(1<<UCSZ02);

	// set the stop bit to 1
	UCSR0C &= ~(1<<USBS0);
	
		
}

void USART_Transmit(char ID[])
{
	// enable the transmitter
	UCSR0B |= (1<<TXEN0);
		
	int i = 0;
	while (ID[i] != '\0')
	{
		while (!(UCSR0A & (1<<UDRE0)));  // wait until the transmit register is cleared
		
		UDR0 = ID[i];
		i++;
	}
	
	//CRLF
	while (!(UCSR0A & 1<<UDRE0)); // wait until the transmit register is cleared
		
	UDR0 = '\n';
	
	while (!(UCSR0A & 1<<UDRE0)); // wait until the transmit register is cleared
	
	UDR0 = '\r';
	
}
	

int main(void)
{
    /* Replace with your application code */
	
	char RedID [] = "825933284";
    while (1) 
    {
		USART_Init(ubrr);
		USART_Transmit(RedID);
		_delay_ms(500);
		
    }
}

