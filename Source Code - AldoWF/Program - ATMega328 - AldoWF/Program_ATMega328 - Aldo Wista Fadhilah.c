/*
 * GccEfishery.c
 *
 * Created: 16/08/2020 06:01:44
 * Author : Aldo Wista Fadhilah
 * Control 24V-DC Motor Using ATMega328 & ESP WROOM-02
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "serial_328cpp.h"

#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)


class serial328
{// Pin 3 (pd1) is TX. Pin 2 (pd0) is RX.
	// UBRR0 = n_clock = frequency/(8*Baud) -1 (Using double clock speed)
	//Baud Rate vs. n_clock (Using double clock speed, f=1MHz)
	//9600 12 = frequency/(8*Baud) -1
	//4800 25 = frequency/(8*Baud) -1
	//2400 51 = frequency/(8*Baud) -1
	//1200 103 = frequency/(8*Baud) -1
	private:
	public:
	#define BAUD9600 12
	#define BAUD4800 25
	#define BAUD2400 51
	#define BAUD1200 103
	#define BAUD0600 207
	void init_rx (unsigned char n_clock); // Initialize USART to receive
	void init_tx (unsigned char n_clock); // Initialize USART to transmit
	void tx (unsigned char value); // Transmit char
	char rx (); // Receive char
	void td (unsigned char x); // Transmit char as a decimal
};
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
void serial328::tx (unsigned char value) // Transmit char
{ while ( (UCSR0A & (1<<UDRE0)) == 0 );//(UDRE0==0);// Wait for transmit ready
	UDR0 = value;
	return;
}
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
char serial328::rx() // Receive char
{ while ( (UCSR0A & (1<<RXC0)) == 0 );// Wait for receive ready. RXC0=1 when done.
	char value = UDR0;
	return (value);
}
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// Initialize USART to receive
void serial328::init_rx (unsigned char n_clock)
{ UBRR0H = 0;
	UBRR0L = n_clock; // Set baud rate to ____. See table.
	UCSR0A |= (1<<U2X0); // 1=double clock speed on
	//UCSR0B |= (1<<TXEN0); // Transmit on
	UCSR0B |= (1<<RXEN0); // Receive on
	//UCSR0C default works also.
	//UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00) | (1<<USBS0); //8 bits, No parity, 2 stop
	return;
} // — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// Initialize USART to transmit
void serial328::init_tx (unsigned char n_clock)
{ UBRR0H = 0;
	UBRR0L = n_clock; // Set baud rate to____. See table.
	UCSR0A |= (1<<U2X0); // 1=double clock speed on
	UCSR0B |= (1<<TXEN0); // Transmit on
	//UCSR0B |= (1<<RXEN0); // Receive on
	//UCSRC0 default works also.
	//UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00) | (1<<USBS0); //8 bits, No parity, 2 stop
	return;
} // — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
// Transmits x in decimal. Transmits it as 3 ascii characters.
void serial328::td (unsigned char x)
{ 
	if (x>=200) {tx('2'); x-= 200; }
else if (x>=100) {tx('1'); x-= 100; }
else {tx('0'); }
if (x>=90) {tx('9'); x-= 90;}
else if (x>=80) {tx('8'); x-= 80;}
else if (x>=70) {tx('7'); x-= 70;}
else if (x>=60) {tx('6'); x-= 60;}
else if (x>=50) {tx('5'); x-= 50;}
else if (x>=40) {tx('4'); x-= 40;}
else if (x>=30) {tx('3'); x-= 30;}
else if (x>=20) {tx('2'); x-= 20;}
else if (x>=10) {tx('1'); x-= 10;}
else {tx('0'); }
if (x>=9 ) {tx('9'); x-= 9 ;}
else if (x>=8 ) {tx('8'); x-= 8 ;}
else if (x>=7 ) {tx('7'); x-= 7 ;}
else if (x>=6 ) {tx('6'); x-= 6 ;}
else if (x>=5 ) {tx('5'); x-= 5 ;}
else if (x>=4 ) {tx('4'); x-= 4 ;}
else if (x>=3 ) {tx('3'); x-= 3 ;}
else if (x>=2 ) {tx('2'); x-= 2 ;}
else if (x>=1 ) {tx('1'); x-= 1 ;}
else {tx('0'); }
return;
}
// — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

void port_init()
{
	DDRD =0b01000011; // Pin 5,4,3,2 in Port D is Input, 6 is OC0A pin that wll produce the PWM.
}

int inputButton;

int main(void)
{
	port_init();
	
	TCCR0A=0b01110101; //Configure TCCR0 

	OCR0A=255; // Set OCR0 to 255 so that the duty cycle is initially 0 and the motor is not rotating
	inputButton = 0;
    while (1) 
    {
		checkInput();		
		while (inputButton= 0)
		{
			OCR0A=255; //If button 1 is pressed, set OCR0=225 (duty cycle=0%).
			checkInput();
		}
		while (inputButton= 1)
		{
			OCR0A=178; //If button 1 is pressed, set OCR0=178 (duty cycle=10%).
			checkInput();
		}
		while (inputButton= 2)
		{
			OCR0A=102; //If button 2 is pressed, set OCR0=102 (duty cycle=60%).
			checkInput();
		}
		while (inputButton= 3)
		{
			OCR0A=25; //If button 3 is pressed, set OCR0=25 (duty cycle=90%).
			checkInput();
		}
		} 
    }
}

void checkInput(){
	serial328 terminalwindow;
	terminalwindow.init_tx(BAUD9600);
	if (get_bit(PIND,2)==1)
	{
		int inputButton=0;
		terminalwindow.tx('0');
	}

	if (get_bit(PIND,3)==1)
	{
		int inputButton=1;
		terminalwindow.tx('1');
	}

	if (get_bit(PIND,4)==1)

	{
		int inputButton=2;
		terminalwindow.tx('2');
	}
	
	if (get_bit(PIND,5)==1)

	{
		int inputButton=3;
		terminalwindow.tx('3');
	}
}








		