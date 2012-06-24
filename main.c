// coding: utf-8
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "rs232.h"

volatile uint8_t rxcmd[4]; // Empfangenes Kommando via serielle Schnittstelle
volatile uint8_t rxcmdcnt; // Zu beschreibendes Byte in rxcmd
volatile uint8_t cmdtimeout;
uint8_t relaisstate;

#define ADRESSE 0x00

void _timer_init(){
	TCCR1B = (1<<CS02)|(1<<CS00);
	TIMSK |= (1<<TOIE1);
}

void init(void){
	_usart_init();
	_timer_init();

	DDRB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7); // Ausgänge für die Relais

	sei();
}

int main(void) {
	init();

	while(1) {
		// Eingangsbuffer prüfen, Relais schalten, Buffer töten
		if (rxcmdcnt > 3){
			if ((rxcmd[0] == 0x01) && (rxcmd[1] == ADRESSE) && (rxcmd[2] != relaisstate) && (rxcmd[0] ^ rxcmd[1] ^ rxcmd[2] == rxcmd[3])){
				PORTB = rxcmd[2];
				relaisstate = rxcmd[2];
			}
		rxcmdcnt = 0;
		}
	}
	return 0;
}

ISR(USART_RXC_vect){
	uint8_t chr = UDR;
	if (rxcmdcnt < 4){
		rxcmd[rxcmdcnt] = chr;
		rxcmdcnt++;
	} else {
		// Vorheriger Wert noch in Bearheitung?
	}
}

ISR(TIMER1_OVF_vect){
	// Tötet den Kommandopuffer
	if (rxcmdcnt == cmdtimeout){
		rxcmdcnt = 0;
	} else {
		cmdtimeout = rxcmdcnt;
	}
}
