#ifndef INCLUDE_ROBOT_CANNON_H
#define INCLUDE_ROBOT_CANNON_H

#include <stdint.h>
#include <arch/antares.h>

typedef enum {
        CANNON_LEFT,
        CANNON_RIGHT
} cannon_t;

void cannon_release(uint8_t cannon);

#endif
