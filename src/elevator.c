#include <robot/elevator.h>

#include <lib/cerebellum/stepper.h>
#include <lib/tmgr.h>

#include <arch/antares.h>

#include <util/delay.h>

ANTARES_INIT_HIGH(elevator_init)
{
        stepper_write(2, 60);
        _delay_ms(100);
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
