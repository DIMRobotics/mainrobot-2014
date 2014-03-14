#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <arch/antares.h>
#include <lib/tmgr.h>

#define mmToTicks(mm) ((motor_path_t) (((motor_path_t) (mm) * 480) / 22))

/*
 * PF0 - relay
 * PB6 - limiter left
 * PE6 - limiter right
 * PC6 - shmorgalka
 */

int main(void)
{
        /* Init background timer */
        TCCR0B = (1<<CS01)|(1<<CS00);
        //TCCR0B = (1<<CS02);
        OCR0A = 250;
        TIMSK0 |= (1<<OCIE0A);

        GPIO_INIT_OUT(GPB7);

        stepper_init();
        
        stepper_enable();

        sei();

        chassis_write(-20, -20);
        while (chassis_busy())
        {
                if (!GPIO_READ(GPB6) && !GPIO_READ(GPE6))
                        break;
        }
        tmgr_delay(50);
        chassis_stop();

        tmgr_delay(300);

        chassis_move(80, 80, 1, 6, mmToTicks(500));
        while (chassis_busy());;

        chassis_move(-80, 80, 1, 7, mmToTicks(144));
        while(chassis_busy());;

        chassis_move(80, 80, 1, 6, mmToTicks(200));
        while (chassis_busy());;

        chassis_move(-80, 80, 1, 7, mmToTicks(144));
        while(chassis_busy());;

        chassis_move(80, 80, 1, 6, mmToTicks(200));
        while (chassis_busy());;

        chassis_move(-80, 80, 1, 7, mmToTicks(144));
        while(chassis_busy());;

        chassis_move(80, 80, 1, 6, mmToTicks(200));
        while (chassis_busy());;

        chassis_move(-80, 80, 1, 7, mmToTicks(144));
        while(chassis_busy());;

        while (1);;;

        /*chassis_move(-80, 80, 1, 7, mmToTicks(144));
        while(chassis_busy());;
        //tmgr_delay(1000);
        chassis_move(80, -80, 1, 7, mmToTicks(144));
        while(chassis_busy());;
        */
        while (1) {
                if (!GPIO_READ(GPB6) && !GPIO_READ(GPE6)) {
                        GPIO_WRITE_LOW(GPB0);
                } else {
                        GPIO_WRITE_HIGH(GPB0);
                }
        }

        while(1);

        return 0;
}

ISR(TIMER0_COMPA_vect)
{
        GPIO_WRITE_HIGH(GPB7);
        tmgr_interrupt();
        chassis_interrupt();
        GPIO_WRITE_LOW(GPB7);
}
