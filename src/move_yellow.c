/**
 * Let's start from the beginning
 */

#include <math.h>

#define ODETECT_FRONT_LIMIT 20
#define ODETECT_REAR_LIMIT 20
#define ODETECT_ROTATE_LIMIT 20
#define ROBOT_RADIUS 143.5
#define ROBOT_ACC 10

#define move_forward(spd, ac_div, path) \
        odetect_set_single_limit(ODETECT_FULLFRONT, ODETECT_FRONT_LIMIT); \
        chassis_move((spd), (spd), 1, (ac_div), mmToTicks((path)))

#define move_backward(spd, ac_div, path) \
        odetect_set_single_limit(ODETECT_REAR, ODETECT_REAR_LIMIT); \
        chassis_move(-(spd), -(spd), 1, (ac_div), mmToTicks((path)))

#define rotate_left(spd, ac_div, angle) \
        odetect_set_single_limit(ODETECT_LEFT, ODETECT_ROTATE_LIMIT); \
        chassis_move(-(spd), (spd), 1, (ac_div), mmToTicks((angle) * M_PI * ROBOT_RADIUS / 180))

#define rotate_right(spd, ac_div, angle) \
        odetect_set_single_limit(ODETECT_RIGHT, ODETECT_ROTATE_LIMIT); \
        chassis_move((spd), -(spd), 1, (ac_div), mmToTicks((angle) * M_PI * ROBOT_RADIUS / 180))

#define chassis_reset(spd) \
        odetect_set_single_limit(0, 0); \
        chassis_write(-(spd), -(spd)); \
        while (GPIO_READ(CONFIG_ROBOT_LIMITER_LEFT) || GPIO_READ(CONFIG_ROBOT_LIMITER_RIGHT)); \
        chassis_write(0, 0); \
        chassis_move(-2, -2, 1, 1, 128); \
        while (chassis_busy()); \
        tmgr_delay(300)

//goto ACTION;

tmgr_delay(500);
chassis_reset(15);

move_forward(50, 14, 110);
while (chassis_busy());

rotate_left(50, ROBOT_ACC, 90);
while (chassis_busy());

chassis_reset(15);

move_forward(50, 14, 70);
while (chassis_busy());

rotate_right(10, ROBOT_ACC, 10);
elevator_set_pos(4500);
servo_write(2, 120);
servo_write(1, 85);

tmgr_delay(500);

while (!GPIO_READ(CONFIG_ROBOT_SHMORGALKA));
while (GPIO_READ(CONFIG_ROBOT_SHMORGALKA)); /* wait for shmorgalka */
timer_run();

/* 1. Go to the first fire on the wall */

move_forward(100, ROBOT_ACC, 630);
while (chassis_busy());

rotate_left(100, ROBOT_ACC, 100);
while (chassis_busy());

tmgr_delay(200);

move_forward(50, ROBOT_ACC, 40);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
while (chassis_busy());

tmgr_delay(200);

move_backward(100, ROBOT_ACC, 110);
elevator_set_pos(1100);
servo_write(2, 25);
tmgr_delay(200);
while (chassis_busy());

rotate_right(100, ROBOT_ACC, 90);
servo_write(1, 160);
tmgr_delay(200);
elevator_set_pos(2000);
tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
while (chassis_busy());

servo_write(1, 85);
servo_write(2, 120);
elevator_set_pos(5700);
tmgr_delay(200);

move_forward(100, ROBOT_ACC, 200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
while (chassis_busy());

move_forward(100, ROBOT_ACC, 690);
elevator_set_pos(2500);
servo_write(2, 25);
servo_write(1, 0);
tmgr_delay(200);
elevator_set_pos(3500);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
while (chassis_busy());

rotate_right(100, ROBOT_ACC, 90);
servo_write(1, 85);
servo_write(2, 120);
tmgr_delay(200);
elevator_set_pos(5700);
while (chassis_busy());

move_forward(100, ROBOT_ACC, 380);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
while (chassis_busy());


move_forward(100, ROBOT_ACC, 175);
elevator_set_pos(2000);
servo_write(2, 25);
tmgr_delay(200);
servo_write(1, 30);
while (chassis_busy());

rotate_right(100, ROBOT_ACC, 90);
servo_write(1, 0);
tmgr_delay(300);
elevator_set_pos(3000);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);
while (chassis_busy());

move_backward(100, ROBOT_ACC, 250);
servo_write(1, 75);
elevator_reset();
while (chassis_busy());

chassis_reset(7);

move_forward(100, ROBOT_ACC, 700);
servo_write(2, 25);
while (chassis_busy());
tmgr_delay(300);
move_backward(100, ROBOT_ACC, 20);
while (chassis_busy());
tmgr_delay(300);

/* collect fires from fireplace */
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(400);
tmgr_delay(200);
elevator_reset();
servo_write(1, 0);
tmgr_delay(300);
elevator_set_pos(1000);
tmgr_delay(200);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);

tmgr_delay(300);

servo_write(1, 75);
tmgr_delay(600);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(2000);
tmgr_delay(400);
elevator_set_pos(300);
servo_write(1, 155);
tmgr_delay(800);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

/* collect last fire */

elevator_reset();
servo_write(1, 75);
tmgr_delay(300);
elevator_set_pos(3200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);
elevator_reset();
servo_write(1, 145);
tmgr_delay(400);
elevator_set_pos(300);

tmgr_delay(400);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);

move_backward(60, ROBOT_ACC, 130);
while (chassis_busy());

rotate_right(100, ROBOT_ACC, 120);
while (chassis_busy());

move_forward(100, ROBOT_ACC, 750);
while (chassis_busy());

servo_write(1, 145);
tmgr_delay(500);
elevator_set_pos(300);

/* Move fires to the fireplace */
elevator_set_pos(600);

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);
elevator_reset();
servo_write(1, 80);
tmgr_delay(300);
elevator_set_pos(3000);
tmgr_delay(200);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(400);

elevator_set_pos(1200);
servo_write(1, 10);
tmgr_delay(500);
elevator_set_pos(1800);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);
elevator_set_pos(1200);

move_backward(60, ROBOT_ACC, 140);
servo_write(1, 80);
tmgr_delay(400);
elevator_set_pos(3200);
while (chassis_busy());

move_forward(60, ROBOT_ACC, 150);
while (chassis_busy());

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

servo_write(2, 25);

elevator_reset();
servo_write(1, 130);
tmgr_delay(300);
elevator_set_pos(2100);
tmgr_delay(300);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(1000);
servo_write(1, 0);
tmgr_delay(600);
elevator_set_pos(2000);
tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

elevator_set_pos(1700);
servo_write(1, 140);
tmgr_delay(500);
elevator_set_pos(3000);
tmgr_delay(200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_set_pos(2600);
servo_write(1, 80);
tmgr_delay(1000);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

/* Now hold fire stack using elevator and go to the central platform */
elevator_reset();
elevator_set_pos(1200);
servo_write(1, 10);
servo_write(2, 25);
tmgr_delay(400);
elevator_set_pos(2000);

move_backward(100, ROBOT_ACC, 200);
while (chassis_busy());

rotate_right(100, ROBOT_ACC, 170);
while (chassis_busy());

move_forward(100, ROBOT_ACC, 1000);
while (chassis_busy());

/* Now we are near central platform */
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(200);

move_backward(100, ROBOT_ACC, 150);
elevator_set_pos(1700);
servo_write(1, 80);
tmgr_delay(500);
elevator_set_pos(3000);
while (chassis_busy());

move_forward(100, ROBOT_ACC, 160);
while (chassis_busy());

elevator_set_pos(2000);
servo_write(2, 170);
tmgr_delay(400);
elevator_set_pos(5800);
move_backward(20, 14, 40);
while (chassis_busy());
tmgr_delay(200);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

move_backward(20, 14, 120);
while (chassis_busy());

servo_write(2, 25);
elevator_set_pos(2200);
servo_write(1, 10);
tmgr_delay(400);
elevator_set_pos(3050);
tmgr_delay(200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_set_pos(2500);
servo_write(1, 80);

move_forward(100, ROBOT_ACC, 130);
while (chassis_busy());

elevator_set_pos(2000);
servo_write(2, 170);
tmgr_delay(400);
elevator_set_pos(5800);
move_backward(20, 14, 10);
while (chassis_busy());
tmgr_delay(200);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

move_backward(20, 14, 130);
while (chassis_busy());

servo_write(2, 25);
elevator_set_pos(3100);
servo_write(1, 10);
tmgr_delay(500);
elevator_set_pos(4400);
tmgr_delay(200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_set_pos(3000);
servo_write(1, 60);
tmgr_delay(200);

move_forward(20, 14, 160);
while (chassis_busy());

tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

move_backward(20, 14, 100);
while (chassis_busy());
