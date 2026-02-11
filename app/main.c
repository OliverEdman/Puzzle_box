/*
 * Project: Puzzle_box
 * Author: Oliver Edman Chrantz 
 * 
 * 
 */ 


#define F_CPU 16000000UL
 
#include <avr/io.h>
#include <util/delay.h>


// Din egenbestämda sekvens (7 steg):

// 0 = LED 1 (PD3)

// 1 = LED 2 (PC4 - Mitten)

// 2 = LED 3 (PC5)

uint8_t sequence[7] = {1, 2, 0, 1, 1, 0, 2};

uint8_t current_level = 1;


void set_led(uint8_t id, uint8_t state) {

    if (state) {

        if (id == 0) PORTD |= (1 << PD3);

        if (id == 1) PORTC |= (1 << PC4);

        if (id == 2) PORTC |= (1 << PC5);

        } else {

        if (id == 0) PORTD &= ~(1 << PD3);

        if (id == 1) PORTC &= ~(1 << PC4);

        if (id == 2) PORTC &= ~(1 << PC5);

    }

}


int8_t get_button() {

    if (!(PIND & (1 << PD5))) return 0;

    if (!(PIND & (1 << PD6))) return 1;

    if (!(PIND & (1 << PD7))) return 2;

    return -1;

}


void show_error_and_reset() {

    // Fel-signal: Alla lyser i 1.5 sek

    set_led(0, 1); set_led(1, 1); set_led(2, 1);

    _delay_ms(1500);

    set_led(0, 0); set_led(1, 0); set_led(2, 0);

    

    while(get_button() != -1); // Vänta tills knapp släpps

    _delay_ms(5000);           // Rejäl paus vid fel (5 sekunder)

    current_level = 1;

}


int main(void) {

    DDRD |= (1 << PD3);

    DDRC |= (1 << PC4) | (1 << PC5);

    DDRB |= (1 << PB5); // Pin 13 för vinst

    

    DDRD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));

    PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);


    while (1) {

        PORTB &= ~(1 << PB5);

        _delay_ms(2500); // Paus innan sekvensen börjar visas


        // 1. VISA SEKVENEN

        for (uint8_t i = 0; i < current_level; i++) {

            set_led(sequence[i], 1);

            _delay_ms(4000); // Lyser i 4 sekunder

            set_led(sequence[i], 0);

            

            // LÄNGRE PAUS MELLAN BLINKEN (2 sekunder)

            if (i < current_level - 1) {

                _delay_ms(2000);

            }

        }


        // 2. VÄNTA PÅ SPELARENS INPUT

        for (uint8_t i = 0; i < current_level; i++) {

            int8_t pressed = -1;

            while(pressed == -1) { pressed = get_button(); }

            

            if (pressed == sequence[i]) {

                set_led(pressed, 1);

                while(get_button() != -1);

                _delay_ms(400);

                set_led(pressed, 0);

                _delay_ms(600); // Paus mellan dina knapptryck

                } else {

                show_error_and_reset();

                goto start_over;

            }

        }


        // 3. NÄSTA NIVÅ ELLER VINST

        if (current_level < 7) {

            current_level++;

            _delay_ms(4000); // LÄNGRE PAUS INNAN NÄSTA NIVÅ VISAS (4 sekunder)

            } else {

            // VINST!

            while(1) {

                PORTB |= (1 << PB5);

                set_led(0,1); set_led(1,1); set_led(2,1);

            }

        }

        start_over: ;

    }

} 
