#include <avr/io.h>
#include <avr/interrupt.h>
#include <arch/antares.h>

#include <lib/cerebellum/gpio.h>

#include <robot/odetect.h>
#include <robot/uart.h>

static volatile enum {
        MODE_IDLE = 0,
        MODE_STATES
} mode;

ANTARES_INIT_LOW(uart_init)
{
        GPIO_INIT_OUT(GPD3);
        GPIO_INIT_IN(GPD2);
        UCSR1B = (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
        UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);
        /* set baudrate 57600 baud */
        UBRR1L = 16;
        UBRR1H = 0;
}

void uart_send(uint8_t ch) {
        UDR1 = ch;
        while (!(UCSR1A & (1<<UDRE1)));
}

static inline void set_mode(uint8_t ch)
{
        switch (ch) {
                case 's':
                        mode = MODE_STATES;
                        break;
                default:
                        mode = MODE_IDLE;
        }
}

static inline void mode_states(uint8_t ch)
{
        static volatile uint8_t i = 0;
        
        odetect_write_state(i, ch == '1');
        i++;
        
        if (ch == 'f') {
                mode = MODE_IDLE;
                i = 0;
        }
}

ISR(USART1_RX_vect)
{
        switch (mode) {
                case MODE_IDLE:
                        set_mode(UDR1);
                        break;
                case MODE_STATES:
                        mode_states(UDR1);
                        break;
        }
}
