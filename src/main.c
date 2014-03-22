#include <lib/cerebellum/gpio.h>
#include <lib/cerebellum/chassis.h>
#include <lib/cerebellum/stepper.h>
#include <util/delay.h>
#include <arch/antares.h>
#include <lib/tmgr.h>

#include <robot/servo.h>
#include <robot/elevator.h>
#include <robot/cannon.h>

#define mmToTicks(mm) ((motor_path_t) (((motor_path_t) (mm) * 480) / 22))

/*
 * PF0 - relay
 * PB6 - limiter left
 * PE6 - limiter right
 * PC6 - shmorgalka
 */

ANTARES_INIT_LOW(init_stepper)
{
        //stepper_init();
        stepper_enable();
}

ANTARES_APP(robot)
{
        while (GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

        /* Continious rotation */
#if 0
        /* Manipulator test */
        while (1) {
                servo_write(1, 0); /* paw */
                servo_write(2, 30); /* direction */
                elevator_set_pos(2000);

                GPIO_WRITE_LOW(GPIO_RELAY);
                tmgr_delay(500);

                elevator_set_pos(1000);
                servo_write(1, 140);
                tmgr_delay(1000);

                GPIO_WRITE_HIGH(GPIO_RELAY);
                tmgr_delay(2000);

                servo_write(1, 0);
                tmgr_delay(1000);
                GPIO_WRITE_LOW(GPIO_RELAY);
                elevator_set_pos(3600);
                tmgr_delay(500);

                elevator_set_pos(0);
                servo_write(1, 140);
                tmgr_delay(1000);
                GPIO_WRITE_HIGH(GPIO_RELAY);
                tmgr_delay(2000); /* both fires are at right side */

                servo_write(1, 90);
                tmgr_delay(500);
                elevator_reset();
                tmgr_delay(1000);

                servo_write(1, 140);
                tmgr_delay(700);
                elevator_set_pos(500);
                GPIO_WRITE_LOW(GPIO_RELAY);
                tmgr_delay(500);

                elevator_reset();
                servo_write(1, 0);
                tmgr_delay(500);
                elevator_set_pos(3000);

                GPIO_WRITE_HIGH(GPIO_RELAY);
                tmgr_delay(2000);

                elevator_set_pos(1200);
                servo_write(1, 140);
                tmgr_delay(1300);
                GPIO_WRITE_LOW(GPIO_RELAY);
                elevator_set_pos(2000);
                tmgr_delay(500);
                
                elevator_set_pos(1000);
                servo_write(1, 0);
                tmgr_delay(1000);

                GPIO_WRITE_HIGH(GPIO_RELAY);
                tmgr_delay(2000);

                servo_write(1, 90);
                tmgr_delay(2000);

                elevator_reset();

                tmgr_delay(3000);
        }

        /* Servo test */
        while (1) {
                servo_write(1, 0);
                servo_write(2, 0);

                tmgr_delay(1000);

                servo_write(1, 180);
                servo_write(2, 180);

                tmgr_delay(1000);
        }

        while (1);
#endif
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

        chassis_move(-80, 80, 1, 7, mmToTicks(224));
        while(chassis_busy());;

        while (1) {
                chassis_move(90, 90, 1, 6, mmToTicks(200));
                while (chassis_busy());;

                chassis_move(-90, 90, 1, 7, mmToTicks(228) + 5);
                while(chassis_busy());;

                chassis_move(90, 90, 1, 6, mmToTicks(200));
                while (chassis_busy());;

                chassis_move(-90, 90, 1, 7, mmToTicks(228) + 5);
                while(chassis_busy());;

                chassis_move(90, 90, 1, 6, mmToTicks(200));
                while (chassis_busy());;

                chassis_move(-90, 90, 1, 7, mmToTicks(228) + 5);
                while(chassis_busy());;
                
                chassis_move(90, 90, 1, 6, mmToTicks(200));
                while (chassis_busy());;

                chassis_move(-90, 90, 1, 7, mmToTicks(228) + 5);
                while(chassis_busy());;
        }

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
}
