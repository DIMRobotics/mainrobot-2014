#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <util/delay.h>
#include <arch/antares.h>
#include <lib/tmgr.h>
#include <lib/printk.h>

#include <robot/servo.h>
#include <robot/elevator.h>
#include <robot/cannon.h>
#include <robot/odetect.h>
#include <robot/uart.h>
#include <robot/timer.h>

#define mmToTicks(mm) ((motor_path_t) (((motor_path_t) (mm) * 480) / 22))


/*
 * PF0 - relay
 * PB6 - limiter left
 * PE6 - limiter right
 * PC6 - shmorgalka
 */

ANTARES_INIT_LOW(init_stepper)
{
        stepper_enable();
}

#define ODETECT_FULLFRONT (ODETECT_FRONT | ODETECT_FRIGHT | ODETECT_FLEFT)
void move_red(void) 
{
#include "move_red.c"
}

void move_yellow(void)
{
#include "move_yellow.c"
}

ANTARES_APP(robot)
{
        chassis_setup_ebrake(1, 3);
        /*cannon_release(CANNON_LEFT);
        odetect_set_single_limit(ODETECT_FRONT, 15);
        odetect_set_single_limit(ODETECT_FRIGHT | ODETECT_FLEFT, 20);
        chassis_move(5, 5, 1, 5, mmToTicks(100));
        tmgr_delay(1000);
        chassis_pause();
        tmgr_delay(2);
        //chassis_resume();
        while (chassis_busy());
        odetect_set_single_limit(ODETECT_FRONT, 0);
        cannon_release(CANNON_LEFT);

        while (1);

        odetect_set_single_limit(ODETECT_REAR, 60);
        while (1) {
                if (odetect_get_state(ODETECT_REAR)) {
                        cannon_release(CANNON_LEFT);
                        cannon_release(CANNON_RIGHT);
                }
        }*/

        if (GPIO_READ(CONFIG_ROBOT_SELECTOR)) {
                move_red();
        } else {
                move_yellow();
        }
        while (1);
}
