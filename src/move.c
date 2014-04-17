while (!GPIO_READ(CONFIG_ROBOT_SHMORGALKA));

tmgr_delay(1000);

/* set start position */
chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
chassis_write(0, 0);

tmgr_delay(200);

chassis_move(20, 20, 1, 7, mmToTicks(220));
while (chassis_busy());

servo_write(1, 95);
servo_write(2, 125);
elevator_set_pos(4500);

/* rotate to -20.07 degrees (-0.350251 radians) */
chassis_move(-100, 100, 1, 7, 840);
while (chassis_busy());

while (GPIO_READ(CONFIG_ROBOT_SHMORGALKA));


/* step 3: go 865.55 mm */
/* handle first fire */
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
chassis_move(100, 100, 1, 7, 27300);
while (stepper_get_path(1) <= 9500);
elevator_set_pos(1000); /* move elevator up */
servo_write(1, 0); /* arm */
servo_write(2, 20); /* paw */
tmgr_delay(500);
elevator_set_pos(2000);
while (chassis_busy());
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);


/* rotate to -36.35 degrees (-0.634347 radians) */
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
/* step 4: go 460.956 mm */
chassis_move(70, 70, 1, 7, 5157);
while (chassis_busy()) { 
	/* do something */
}
elevator_set_pos(100);
servo_write(1, 0);
servo_write(2, 20);
tmgr_delay(500);
elevator_set_pos(1900);

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
elevator_reset();

while (1);
/* rotate to -33.59 degrees (-0.586204 radians) */
chassis_move(-100, 100, 1, 7, 1803);
while (chassis_busy()) {
	/*do something */
}

/* step 5: go 852.006 mm */
chassis_move(100, 100, 1, 7, 18589);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to 90.00 degrees (1.570800 radians) */
chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy()) {
	/*do something */
}

/* step 6: go 153 mm */
chassis_move(100, 100, 1, 7, 3338);
while (chassis_busy()) { 
	/* do something */
}

/* step 7: go 9.33333 mm */
chassis_move(100, 100, 1, 7, 204);
while (chassis_busy()) { 
	/* do something */
}

