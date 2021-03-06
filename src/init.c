#include <arch/antares.h>

#include <lib/cerebellum/gpio.h>

#define GPIO_SHMORGALKA GPC6
#define GPIO_LIMITER_LEFT GPB6
#define GPIO_LIMITER_RIGHT GPE6
#define GPIO_RELAY GPF0
ANTARES_INIT_LOW(init_gpio)
{
        /* init relay */
        GPIO_INIT_OUT(GPIO_RELAY);
        GPIO_WRITE_HIGH(GPIO_RELAY);

        /* init sensors */
        GPIO_INIT_IN(GPIO_LIMITER_LEFT);
        GPIO_INIT_IN(GPIO_LIMITER_RIGHT);
        GPIO_INIT_IN(GPIO_SHMORGALKA);

        /* init status LED */
        GPIO_INIT_OUT(GPB0);
        GPIO_WRITE_LOW(GPB0);
}
