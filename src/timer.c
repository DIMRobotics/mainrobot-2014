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

static volatile int32_t timer = -1;

void timer_run(void)
{
        timer = 91000;
}

ISR(TIMER0_COMPA_vect)
{
        sei();
        tmgr_interrupt();
        chassis_interrupt();
        if (timer >= 0) {
                timer--;
                
                if (timer == 0) {
                        GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
                        while (1);; /* robot shutdown */
                }
        }
}
