#ifndef INCLUDE_ROBOT_SERVO_H
#define INCLUDE_ROBOT_SERVO_H

#include <lib/cerebellum/gpio.h>

#define SERVO_MIN 500
#define SERVO_MAX 2500

void servo_write(uint8_t servo, uint16_t value);
void servo_write_us(uint8_t servo, uint16_t value);

#endif
