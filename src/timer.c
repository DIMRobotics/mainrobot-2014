#include <arch/antares.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <lib/tmgr.h>
#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>

ANTARES_INIT_LOW(maintimer_init)
{
        TCCR0B = (1<<CS01)|(1<<CS00);
        OCR0A = 250;
        TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
        sei();
        tmgr_interrupt();
        chassis_interrupt();
}
