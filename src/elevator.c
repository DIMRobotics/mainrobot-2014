#include <robot/elevator.h>
#include <robot/servo.h>

#include <lib/cerebellum/stepper.h>
#include <lib/cerebellum/gpio.h>
#include <lib/tmgr.h>

#include <arch/antares.h>

#include <util/delay.h>


ANTARES_INIT_HIGH(elevator_init)
{
        GPIO_INIT_IN_PU(CONFIG_ROBOT_ELEVRESET);
        servo_write(1, 0);
        elevator_reset();
}

void elevator_reset(void)
{
        stepper_write(2, 50);
        while (GPIO_READ(CONFIG_ROBOT_ELEVRESET));;;
        stepper_write(2, 0);
        stepper_reset_path(2);
}

void elevator_slow_reset(void)
{
        stepper_write(2, 10);
        while (GPIO_READ(CONFIG_ROBOT_ELEVRESET));;;
        stepper_write(2, 0);
        stepper_reset_path(2);
}

void elevator_set_pos(int16_t pos)
{
        pos = -pos;
        if (pos > stepper_get_path(2)) {
                stepper_write(2, 50);
                while (stepper_get_path(2) < pos);
        } else {
                stepper_write(2, -50);
                while (stepper_get_path(2) > pos);
        }
        stepper_write(2, 0);
}


