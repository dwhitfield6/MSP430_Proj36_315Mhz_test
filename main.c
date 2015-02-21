//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************

#include <msp430.h>				

#define TX BIT3

void send_rf(unsigned char, unsigned char*);
void zero(unsigned char);
void one(unsigned char);
void f(unsigned char);

unsigned char TXdata[12] = {0,2,2,2,2,2,0,0,1,0,0,0};

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P2DIR |= TX;					// Set P1.0 to output direction

	while(1)
	{
		send_rf(TX, TXdata);
		send_rf(TX, TXdata);
		send_rf(TX, TXdata);
		send_rf(TX, TXdata);
		_delay_cycles(1000000);
	}
}

void send_rf(unsigned char pin, unsigned char* data)
{
unsigned char i=0;

for(i=0;i<12;i++)
{
if(data[i] == 0)
{
	zero(pin);
}
else if(data[i] ==1)
{
	one(pin);
}
else
{
	f(pin);
}

}

P2OUT |= pin;
_delay_cycles(250);
P2OUT &= ~pin;
_delay_cycles(7000);
}

void zero(unsigned char pin)
{
	P2OUT |= pin;
	_delay_cycles(250);
	P2OUT &= ~pin;
	_delay_cycles(690);
	P2OUT |= pin;
	_delay_cycles(250);
	P2OUT &= ~pin;
	_delay_cycles(690);
}
void one(unsigned char pin)
{
	P2OUT |= pin;
	_delay_cycles(810);
	P2OUT &= ~pin;
	_delay_cycles(210);
	P2OUT |= pin;
	_delay_cycles(810);
	P2OUT &= ~pin;
	_delay_cycles(210);
}
void f(unsigned char pin)
{
	P2OUT |= pin;
	_delay_cycles(250);
	P2OUT &= ~pin;
	_delay_cycles(700);
	P2OUT |= pin;
	_delay_cycles(810);
	P2OUT &= ~pin;
	_delay_cycles(200);
}
