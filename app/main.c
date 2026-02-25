/*
 * Project: Puzzle_box
 * Author: Oliver Edman Chrantz 
 * 
 * 
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


/* - TYPER OCH KONSTANTER */

typedef enum { SHOW_SEQ, PAUSE, WAIT_BTN, RESET, WINNER } state_t;


/* GLOBALA VARIABLER (volatile  ISR) */

volatile uint32_t ms_ticks = 0;

volatile int8_t last_button = -1;  // -1 beacuse 1 is button relase and 0 is press 

volatile uint32_t last_interrupt_time = 0; // debounce 


uint8_t sequence[7] = {1, 2, 0, 1, 1, 0, 2};

/*  TIMER OCH TID 
 By using a prescaler of 64, the timer receives one tick for every 64 CPU clock cycles.
 This reduces the frequency from 16,000,000 Hz (cycles/sec) to 250,000 ticks per second. 
 The timer counts from 0 to 249 (which is 250 steps). Since it completes one full cycle 1,000 times every second,
 each cycle represents exactly 1 millisecond.*/

void setup_timer0(void) {

    TCCR0A = (1 << WGM01);              // CTC mode

    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64

    OCR0A = 249;                        // 1ms vid 16MHz

    TIMSK0 |= (1 << OCIE0A);            // Enable interrupt


/*ms_ticks add 1 every mille second*/
}


ISR(TIMER0_COMPA_vect) {

    ms_ticks++;

}

/* This function gives us the current time in milliseconds. 
 * It briefly pauses interrupts (cli and sei) to make sure 
 * we read the time correctly without any errors. 
 * This is necessary because the processor is 8-bit and 
 * the time variable is 32-bit; we could get wrong numbers 
 * because the processor cannot read all 32 bits as fast 
 * as the clock ticks. */

uint32_t millis(void) {

    uint32_t m;

    cli(); m = ms_ticks; sei();

    return m;

}

/*This functions can turn on or off led*/


void set_led(uint8_t id, uint8_t state) {

    if (state) {

        // turn on leds

        if (id == 0) PORTD |= (1 << PD3);

        if (id == 1) PORTC |= (1 << PC4);

        if (id == 2) PORTC |= (1 << PC5);

        if (id == 3) PORTB |= (1 << PB5); // Vinst-lampa

    } else {


        if (id == 0) PORTD &= ~(1 << PD3);

        if (id == 1) PORTC &= ~(1 << PC4);

        if (id == 2) PORTC &= ~(1 << PC5);

        if (id == 3) PORTB &= ~(1 << PB5); // Vinst-lampa

    }

}


/* --- AVBROTT FÖR KNAPPAR --- */

ISR(PCINT2_vect) {

    uint8_t pins = PIND;

    uint32_t now = ms_ticks;

   

    if (now - last_interrupt_time > 250) {

        if (!(pins & (1 << PD5))) last_button = 0;

        else if (!(pins & (1 << PD6))) last_button = 1;

        else if (!(pins & (1 << PD7))) last_button = 2;

        last_interrupt_time = now;

    }

}


void setup_hardware(void) {

    DDRD |= (1 << PD3);

    DDRC |= (1 << PC4) | (1 << PC5);

    DDRB |= (1 << PB5);


    DDRD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));

    PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);


    setup_timer0();


    PCICR |= (1 << PCIE2);

    PCMSK2 |= (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23);


    sei();
 
}


/* --- PUSSEL-LOGIK --- */

uint8_t simon_says(void) {

    static state_t state = SHOW_SEQ;

    static uint8_t level = 1;

    static uint8_t step = 0;

    static uint32_t timer = 0;

    static uint8_t led_active = 0;


    uint32_t now = millis();


    switch (state) {

        case SHOW_SEQ:

            if (!led_active) {

                set_led(sequence[step], 1);

                led_active = 1;

                timer = now;

            }


            if (now - timer >= 1000) {

                set_led(sequence[step], 0);

                led_active = 0;

                step++;

               

                if (step < level) {

                    state = PAUSE;

                    timer = now;

                } else {

                    step = 0;

                    last_button = -1;

                    state = WAIT_BTN;

                }

            }

            break;


        case PAUSE:

            if (now - timer >= 300) {

                state = SHOW_SEQ;

            }

            break;


        case WAIT_BTN:

            if (last_button != -1) {

                if (last_button == sequence[step]) {

                    set_led(last_button, 1);

                    uint32_t flash = millis(); while(millis() - flash < 200);

                    set_led(last_button, 0);


                    step++;

                    last_button = -1;


                    if (step >= level) {

                        if (level >= 7) return 1;

                        level++;

                        step = 0;

                        timer = now;

                        state = PAUSE;

                    }

                } else {

                    state = RESET;

                    timer = now;

                }

            }

            break;


        case RESET:

            set_led(0, 1); set_led(1, 1); set_led(2, 1);

            if (now - timer >= 1000) {

                set_led(0, 0); set_led(1, 0); set_led(2, 0);

                level = 1;

                step = 0;

                state = SHOW_SEQ;

            }

            break;

    }

    return 0;

}


/* --- MAIN LOOP --- */

int main(void) {

    setup_hardware();


    while (1) {

        if (simon_says() == 1) {

            // Tänd vinst-lampan (Pin 13)

            PORTB |= (1 << PB5);

           

            // Tänd alla pussel-lampor permanent

            set_led(0, 1);

            set_led(1, 1);

            set_led(2, 1);

            set_led(3, 1);


            // Stanna här för att låta allt lysa

            while(1);

        }

    }

} 