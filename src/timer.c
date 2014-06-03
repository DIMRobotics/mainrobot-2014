#include <arch/antares.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <lib/tmgr.h>
#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <robot/odetect.h>

ANTARES_INIT_LOW(maintimer_init)
{
        TCCR0B = (1<<CS01)|(1<<CS00);
        OCR0A = 250;
        TIMSK0 |= (1<<OCIE0A);
}

static volatile int32_t timer = -1;

void timer_run(void)
{
        timer = 87000;
}

ISR(TIMER0_COMPA_vect)
{
        sei();
        GPIO_WRITE_LOW(GPB0);
        tmgr_interrupt();
        odetect_interrupt();
        chassis_interrupt();
        if (timer > 0) {
                timer--;
                
                if (timer == 0) {
                        GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
                        GPIO_WRITE_HIGH(GPB0);
                        stepper_set_speed(0, 0);
                        stepper_set_speed(1, 0);
                        stepper_set_speed(2, 0);
                        TCCR0B = 0;
                        cli();
                        while (1);; /* robot shutdown */
                }
        }
        GPIO_WRITE_HIGH(GPB1);
}
