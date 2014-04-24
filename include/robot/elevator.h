#ifndef INCLUDE_ROBOT_ELEVATOR_H
#define INCLUDE_ROBOT_ELEVATOR_H

#include <stdint.h>

void elevator_reset(void);
void elevator_slow_reset(void);
void elevator_set_pos(int16_t pos);

#endif
