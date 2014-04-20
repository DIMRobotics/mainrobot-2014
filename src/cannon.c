#include <robot/cannon.h>

#include <robot/servo.h>

ANTARES_INIT_LOW(cannon_init)
{
        servo_write(3, 140);
        servo_write(4, 0);
}

void cannon_release(uint8_t cannon)
{
        if (cannon == CANNON_LEFT)
                servo_write(3, 100);
        else if (cannon == CANNON_RIGHT)
                servo_write(4, 50);
}
