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

//goto ACTION;

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
/* rotate to -90.00 degrees (-1.570790 radians) */
/*!angle: -1.57079 */
chassis_move(-100, 100, 1, 7, 4832);
while (chassis_busy()) {
	/*do something */
}
#endif

chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy());

/*!speed: 100 */

/*!path: 1372 */
chassis_move(100, 100, 1, 7, 29935);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -48.12 degrees (-0.839928 radians) */
/*!angle: -0.839928 */
chassis_move(-100, 100, 1, 7, 2584);
while (chassis_busy()) {
	/*do something */
}

/*!path: 116.849 */
chassis_move(100, 100, 1, 7, 2549);
while (chassis_busy());

elevator_reset();
servo_write(1, 0);
servo_write(2, 27);
tmgr_delay(400);
elevator_set_pos(1900);

//chassis_move(40, 40, 1, 7, mmToTicks(30));
//while (chassis_busy());

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(1000);

servo_write(1, 80);
tmgr_delay(300);
servo_write(2, 180);
tmgr_delay(300);

elevator_set_pos(4500);

chassis_move(40, 40, 1, 7, mmToTicks(30));
while (chassis_busy());

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

chassis_move(-10, -10, 1, 30 ,mmToTicks(80));
while (chassis_busy());

servo_write(2, 27);
elevator_set_pos(1500);
servo_write(1, 0);
elevator_set_pos(3300);

GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(100);

elevator_set_pos(1700);

servo_write(1, 80);
tmgr_delay(100);

chassis_move(40, 40, 1, 7, mmToTicks(70));
while (chassis_busy());

GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(400);

chassis_move(-50, -50, 1, 7, mmToTicks(20));
while (chassis_busy());

#if 0
/* rotate to 180.00 degrees (3.141590 radians) */
/*!angle: 3.14159 */
chassis_move(100, -100, 1, 7, 9665);
while (chassis_busy()) {
	/*do something */
}

/*!path: 1 */
chassis_move(100, 100, 1, 7, 22);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -0.83 degrees (-0.014443 radians) */
/*!angle: -0.0144428 */
chassis_move(-100, 100, 1, 7, 44);
while (chassis_busy()) {
	/*do something */
}

#endif
/*!speed: -100 */
/*!path: 122.329 */
chassis_move(-100, -100, 1, 7, 2669);
servo_write(1, 0);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -19.43 degrees (-0.339176 radians) */
/*!angle: -0.415704 */
chassis_move(-100, 100, 1, 7, 1279);
while (chassis_busy()) {
	/*do something */
}

/*!path: 992.542 */
chassis_move(-100, -100, 1, 7, 21655);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -21.62 degrees (-0.377253 radians) */
/*!angle: -0.312916 */
chassis_move(-100, 100, 1, 7, 963);
while (chassis_busy()) {
	/*do something */
}

/*!path: 246.018 */
chassis_move(-100, -100, 1, 7, 5368);
while (chassis_busy()) { 
	/* do something */
}

/* go back until the wall is detected */
chassis_write(-15, -15);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(100);
chassis_write(0, 0);

/* let's reset position */
chassis_move(70, 70, 1, 7, mmToTicks(150));
while (chassis_busy());

chassis_move(-100, 100, 1, 7, 4832);
while (chassis_busy());

chassis_move(-70, -70, 1, 7, mmToTicks(400));
while (chassis_busy());

chassis_write(-15, -15);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(100);
chassis_write(0, 0);

/* go forward 60 cm */
chassis_move(70, 70, 1, 7, mmToTicks(600));
while (chassis_busy());

chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy());

chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(100);
chassis_write(0, 0);

tmgr_delay(1000); /* establish position */
cannon_release(CANNON_LEFT);
tmgr_delay(1000);

#if 0
/* rotate to -179.30 degrees (-3.129400 radians) */
/*!angle: -3.1294 */
chassis_move(-100, 100, 1, 7, 9627);
while (chassis_busy()) {
	/*do something */
}
#endif

/*!speed: 100 */

/*!path: 105 */
chassis_move(100, 100, 1, 7, 2291);
while (chassis_busy()) { 
	/* do something */
}

/* rotate to -52.71 degrees (-0.920026 radians) */
/*!angle: -0.920026 */
chassis_move(-100, 100, 1, 7, 2830);
while (chassis_busy()) {
	/*do something */
}

/*!path: 742.82 */
chassis_move(100, 100, 1, 7, 16207);
while (chassis_busy()) { 
	/* do something */
}

elevator_reset();
chassis_write(1, 5);
tmgr_delay(1000);
chassis_write(0, 0);


servo_write(1, 140);
servo_write(2, 27);

tmgr_delay(1000);

elevator_set_pos(370);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);

tmgr_delay(300);
elevator_set_pos(20);

servo_write(1, 80);
tmgr_delay(300);
servo_write(2, 180);
tmgr_delay(300);

elevator_set_pos(4400);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);

chassis_move(-10, -10, 1, 24, mmToTicks(50));
while (chassis_busy());

chassis_move(10, 10, 1, 24, mmToTicks(50));
while (chassis_busy());

elevator_set_pos(1300);
servo_write(1, 140);
servo_write(2, 27);
tmgr_delay(500);

elevator_set_pos(2000);
tmgr_delay(200);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
elevator_set_pos(1600);

servo_write(1, 80);
tmgr_delay(600);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);

chassis_move(-80, -80, 1, 7, mmToTicks(350));
servo_write(1, 0);
elevator_reset();
while (chassis_busy());

chassis_move(100, -100, 1, 7, 3100);
while (chassis_busy());


chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(100);
chassis_write(0, 0);

chassis_move(70, 70, 1, 7, mmToTicks(150));
while (chassis_busy());

chassis_move(-100, 100, 1, 7, 4832);
while (chassis_busy());

chassis_move(100, 100, 1, 7, mmToTicks(1430));
while (chassis_busy());

chassis_move(100, -100, 1, 7, 4832);
while (chassis_busy());

chassis_write(-20, -20);
while (GPIO_READ(GPB6) || GPIO_READ(GPE6)); /* wait for limiters */
tmgr_delay(100);
chassis_write(0, 0);

tmgr_delay(1000);
cannon_release(CANNON_RIGHT);
tmgr_delay(1000);

#if 0
/* rotate to 117.14 degrees (2.044420 radians) */
/*!angle: -1.12439 */
chassis_move(-100, 100, 1, 7, 3459);
while (chassis_busy()) {
	/*do something */
}

/*!path: 1210.22 */
chassis_move(100, 100, 1, 7, 26405);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to 74.53 degrees (1.300770 radians) */
/*!angle: 2.04442 */
chassis_move(100, -100, 1, 7, 6289);
while (chassis_busy()) {
	/*do something */
}
#endif

/*!speed: 100 */
/*!path: 135 */
chassis_move(100, 100, 1, 7, 2945);
while (chassis_busy()) { 
	/* do something */
}
/* rotate to -19.34 degrees (-0.337582 radians) */
/*!angle: 1.37069 */
chassis_move(100, -100, 1, 7, 4217);
while (chassis_busy()) {
	/*do something */
}

/*!path: 1086.69 */
chassis_move(100, 100, 1, 7, 23710);
while (chassis_busy()) { 
	/* do something */
}

/* rotate to -32.20 degrees (-0.562049 radians) */
/*!angle: -0.562049 */
chassis_move(-100, 100, 1, 7, 1729);
while (chassis_busy()) {
	/*do something */
}

/*!path: 547.448 */
chassis_move(100, 100, 1, 7, 11944);
while (chassis_busy()) { 
	/* do something */
}


/* Let's do some magic with candles */
elevator_reset();
servo_write(2, 180);
tmgr_delay(800);
servo_write(1, 150);
tmgr_delay(800);
servo_write(2, 27);
tmgr_delay(800);
servo_write(1, 35);
tmgr_delay(500);

/* First fire is ready */

elevator_reset();
servo_write(1, 63);
servo_write(2, 27);
chassis_move(-10, -10, 1, 7, mmToTicks(45));
while (chassis_busy());

tmgr_delay(800);

elevator_set_pos(700);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_reset();

tmgr_delay(500);

chassis_move(-10, -10, 1, 7, mmToTicks(40));
for (uint8_t i=27; i!=90; i++) {
        servo_write(2, i);
        tmgr_delay(30);
}
while (chassis_busy());
servo_write(2, 170);

chassis_move(-30, -30, 1, 7, mmToTicks(100));
elevator_set_pos(5500);
while (chassis_busy());

chassis_move(-100, 100, 1, 7, 2500);
while (chassis_busy());

chassis_move(30, 30, 1, 7, mmToTicks(50));
while (chassis_busy());

tmgr_delay(500);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(500);

chassis_move(-30, -30, 1, 20, mmToTicks(50));
elevator_reset();
while (chassis_busy());

chassis_move(100, -100, 1, 7, 2500);
while (chassis_busy());

chassis_move(30, 30, 1, 7, mmToTicks(190));
while (chassis_busy());

/* take last */
servo_write(1, 63);
servo_write(2, 27);

tmgr_delay(800);

elevator_set_pos(2000);
GPIO_WRITE_LOW(CONFIG_ROBOT_VACUUM);
tmgr_delay(300);
elevator_reset();

tmgr_delay(500);


chassis_move(-10, -10, 1, 7, mmToTicks(40));
for (uint8_t i=27; i!=90; i++) {
        servo_write(2, i);
        tmgr_delay(30);
}
while (chassis_busy());
servo_write(2, 170);

chassis_move(-30, -30, 1, 7, mmToTicks(150));
while (chassis_busy());

chassis_move(100, -100, 1, 7, 2500);
servo_write(2, 27);
while (chassis_busy());

chassis_move(30, 30, 1, 7, mmToTicks(50));
while (chassis_busy());

tmgr_delay(500);
GPIO_WRITE_HIGH(CONFIG_ROBOT_VACUUM);
tmgr_delay(500);

chassis_move(-30, -30, 1, 20, mmToTicks(50));
elevator_reset();
while (chassis_busy());
