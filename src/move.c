/* robot description: */
/*!res_num: 480 */
/*!res_den: 22 */
/*!radius: 141 */
/*!speed: 100 */
/*!acc_num: 1 */
/*!acc_den: 7 */
/*!rspeed: 100 */
/*!racc_num: 1 */
/*!racc_den: 7 */

/* place robot at start point */
/* note that robot must be placed at OX direction */
/*!coords: 222 236 */

while (!GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

tmgr_delay(1000);

/* set start position */
chassis_write(-3, -3);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(300);
chassis_write(0, 0);
tmgr_delay(1000);

chassis_move(20, 20, 1, 15, mmToTicks(220));
while (chassis_busy());

servo_write(1, 106);
servo_write(2, 125);
elevator_set_pos(5000);

/* set start angle */
/*!angle: -0.311746 */
chassis_move(-100, 100, 1, 7, 959);
while (chassis_busy()) {
	/* do something */
}

chassis_move(-20, -20, 1, 15, mmToTicks(30));
while(chassis_busy());

/* wait for shmorgalka to launch */
while (GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);

/* step 2: go 1237.04 mm */
/*!path: 1359.53 */
chassis_move(100, 100, 1, 7, 29662);
while (stepper_get_path(1) <= 9600);
elevator_set_pos(2200); /* move elevator up */
servo_write(1, 0); /* arm */
servo_write(2, 20); /* paw */
tmgr_delay(300);
elevator_set_pos(2800);
tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_set_pos(2400);
servo_write(1, 90);
servo_write(2, 125);
while (chassis_busy());


/* rotate to -68.88 degrees (-1.202230 radians) */
/*!angle: -1.2421 */
chassis_move(-100, 100, 1, 7, 3821);
elevator_set_pos(5000);
while (chassis_busy()) {
	/*do something */
}


GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
/* step 3: go 817.966 mm */
/*!path: 708.105 */
chassis_move(100, 100, 1, 7, 15450);

while (stepper_get_path(1) <= mmToTicks(70));
elevator_set_pos(100);
servo_write(1, 0);
servo_write(2, 20);
tmgr_delay(500);
elevator_set_pos(1900);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
elevator_reset();

while (chassis_busy());

/*!speed: 50 */

/* rotate to 83.68 degrees (1.460540 radians) */
/*!angle: 1.55385 */
chassis_move(100, -100, 1, 7, 4780);
servo_write(1, 90);
servo_write(2, 125);
tmgr_delay(100);
elevator_set_pos(4500);
while (chassis_busy());


/* step 4: go 183 mm */
/*!path: 186.002 */
chassis_move(50, 50, 1, 7, 4058);
while (chassis_busy());


GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
chassis_move(10, 10, 1, 7, mmToTicks(6));
while (chassis_busy());

chassis_move(-10, -10, 1, 7, mmToTicks(6));
while (chassis_busy());

/* go away from this side-hell! :D */
chassis_move(-50, -50, 1, 7, 4058);
tmgr_delay(300);
elevator_set_pos(1000);
servo_write(2, 20);
elevator_set_pos(400);
servo_write(1, 150);

tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);

while (chassis_busy());

#if 0
/* rotate to 180.00 degrees (3.141590 radians) */
/*!angle: 3.14159 */
chassis_move(100, -100, 1, 7, 9665);
while (chassis_busy()) {
	/*do something */
}

/*!path: 186.002 */
chassis_move(50, 50, 1, 7, 4058);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to 90.00 degrees (1.570790 radians) */
/*!angle: 1.57079 */
chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy()) {
	/*do something */
}
#endif
chassis_move(-100, 100, 1, 7, 4832);
while (chassis_busy());

/*!path: 415 */
chassis_move(50, 50, 1, 7, 9055);
elevator_reset();
while (chassis_busy()) { 
	/* do something */
}
/* rotate to 90.00 degrees (1.570800 radians) */
/*!angle: 1.5708 */
chassis_move(100, -100, 1, 7, 4832);
servo_write(1, 90);
servo_write(2, 125);
elevator_set_pos(4500);
while (chassis_busy());

/*!path: 186 */
chassis_move(50, 50, 1, 7, 4058);
while (chassis_busy()) { 
	/* do something */
}

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
chassis_move(10, 10, 1, 7, mmToTicks(6));
while (chassis_busy());

chassis_move(-10, -10, 1, 7, mmToTicks(6));
while (chassis_busy());

chassis_move(-50, -50, 1, 7, 4058);
tmgr_delay(300);
elevator_set_pos(1000);
servo_write(2, 20);
elevator_reset();
servo_write(1, 150);

tmgr_delay(300);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
while (chassis_busy());
