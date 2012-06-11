// coding: utf-8
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "rs232.h"

void init(void){
	_usart_init();

	// Ausgänge hier initialisieren

	// Timer hier initialisieren
	sei();
}

int main(void) {
	init();

	while(1) {
		// Eingangsbuffer prüfen, Relais schalten, Buffer töten
	}
	return 0;
}

ISR(USART_RXC_vect){
	uint8_t chr = UDR;
	// Zeichen in den Eingangsbuffer verschieben
}

ISR(TIMER0_OVF_vect){
	// Periodisch den Eingangsbuffer töten
}
