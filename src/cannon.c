#include <robot/cannon.h>

#include <robot/servo.h>

ANTARES_INIT_HIGH(cannon_init)
{
        servo_write(3, 70);
        servo_write(4, 110);
}

void cannon_release(uint8_t cannon)
{
        if (cannon == CANNON_LEFT)
                servo_write(3, 0);
        else if (cannon == CANNON_RIGHT)
                servo_write(4, 180);
}
