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
/*!coords: 54 103 */


/* waint for shmorgalka to init */
while (!GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

tmgr_delay(1000);

/* set start position */
chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
chassis_write(0, 0);
tmgr_delay(1000);

chassis_move(20, 20, 1, 7, mmToTicks(220));
while (chassis_busy());

servo_write(1, 95);
servo_write(2, 125);
elevator_set_pos(4500);

/* set start angle */
/*!angle -0.2730496 */
chassis_move(-100, 100, 1, 7, 840);
while (chassis_busy());

/* wait for shmorgalka to launch */
while (GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

/* get ready to handle first fire */
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);

/* step 3: go 865.55 mm */
/*!path: 1251.25 */
chassis_move(100, 100, 1, 7, 27300);

while (stepper_get_path(1) <= 9500);
elevator_set_pos(1000); /* move elevator up */
servo_write(1, 0); /* arm */
servo_write(2, 20); /* paw */
tmgr_delay(500);
elevator_set_pos(2000);
while (chassis_busy());
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);

/*!angle: -0.9592494 */
chassis_move(-100, 100, 1, 7, 2951);
while (chassis_busy()) {
	/*do something */
}

servo_write(1, 75);
servo_write(2, 115);
tmgr_delay(500);
elevator_set_pos(4500);
tmgr_delay(500);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
/* first fire is on board now */


/* go to second fire */
/*!path: 236.3625 */
chassis_move(70, 70, 1, 7, 5157);
while (chassis_busy());

/* second fire is handled */
elevator_set_pos(100);
servo_write(1, 0);
servo_write(2, 20);
tmgr_delay(500);
elevator_set_pos(1900);

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
/* second fire is on board */

elevator_reset();
