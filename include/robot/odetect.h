#ifndef INCLUDE_ROBOT_ODETECT_H
#define INCLUDE_ROBOT_ODETECT_H

#include <stdint.h>

typedef enum {
        ODETECT_REAR = (1<<2),
        ODETECT_RIGHT = (1<<0),
        ODETECT_FRONT = (1<<1),
        ODETECT_LEFT = (1<<3),
        ODETECT_FLEFT = (1<<4),
        ODETECT_FRIGHT = (1<<5)
} odetect_dir_t;

void odetect_set_limit(odetect_dir_t dir, uint8_t limit);
void odetect_set_single_limit(odetect_dir_t dir, uint8_t limit);
uint8_t odetect_get_state(odetect_dir_t dir);
void odetect_write_state(odetect_dir_t dir, uint8_t state);

#endif
