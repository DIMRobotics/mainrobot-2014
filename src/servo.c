#include <robot/servo.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <arch/antares.h>

static void servo_sort(void);

static volatile struct servo_struct {
        volatile uint8_t i;
        volatile uint16_t value;
        volatile uint16_t next_value;
} servo_queue[CONFIG_ROBOT_NUM_SERVO];

static volatile uint8_t servo_ready = 0;

ANTARES_INIT_LOW(servo_init)
{
        /* init servo GPIO to out */
#ifdef CONFIG_ROBOT_SERVO1
        GPIO_INIT_OUT(CONFIG_ROBOT_SERVO1);
#endif
#ifdef CONFIG_ROBOT_SERVO2
        GPIO_INIT_OUT(CONFIG_ROBOT_SERVO2);
#endif
#ifdef CONFIG_ROBOT_SERVO3
        GPIO_INIT_OUT(CONFIG_ROBOT_SERVO3);
#endif
#ifdef CONFIG_ROBOT_SERVO4
        GPIO_INIT_OUT(CONFIG_ROBOT_SERVO4);
#endif

        /* init base timer */
        /* timer 1 for example */
        TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
        TIMSK1 |= (1<<TOIE1)|(1<<OCIE1A); /* one compare vector */

        /* clear base structure */
        for (uint8_t i=0; i<CONFIG_ROBOT_NUM_SERVO; i++) {
                servo_queue[i].i = i+1;
                servo_queue[i].value = 0;
                servo_queue[i].next_value = 65535;
        }

        servo_ready = 1;
}

void servo_write_us(uint8_t servo, uint16_t value)
{
        ANTARES_ATOMIC_BLOCK() {
                for (uint8_t i=0; i<CONFIG_ROBOT_NUM_SERVO; i++) {
                        if (servo_queue[i].i == servo) {
                                servo_ready = 0;
                                servo_queue[i].next_value = value >> 2;
                                break;
                        }
                }
        }
}

void servo_write(uint8_t servo, uint16_t value)
{
        value = SERVO_MIN + (((value * 25) / 9 ) << 2);
        servo_write_us(servo, value);
}

static void servo_sort(void)
{
        for (uint8_t i=0; i<CONFIG_ROBOT_NUM_SERVO; i++) {
                if (servo_queue[i].next_value != 65535) {
                        servo_queue[i].value = servo_queue[i].next_value;
                        servo_queue[i].next_value = 65535;
                }
        }

        for (uint8_t i=0; i<CONFIG_ROBOT_NUM_SERVO; i++) {
                for (uint8_t j=i+1; j<CONFIG_ROBOT_NUM_SERVO; j++) {
                        if (servo_queue[i].value > servo_queue[j].value) {
                                uint16_t v_tmp = servo_queue[i].value;
                                uint8_t i_tmp = servo_queue[i].i;
                                servo_queue[i].value = servo_queue[j].value;
                                servo_queue[i].i = servo_queue[j].i;
                                servo_queue[j].value = v_tmp;
                                servo_queue[j].i = i_tmp;
                        }
                }
        }
}

static void servo_off(uint8_t servo)
{
#ifdef CONFIG_ROBOT_SERVO1
        if (servo == 1) 
                GPIO_WRITE_LOW(CONFIG_ROBOT_SERVO1);
#endif
#ifdef CONFIG_ROBOT_SERVO2
        else if (servo == 2) 
                GPIO_WRITE_LOW(CONFIG_ROBOT_SERVO2);
#endif
#ifdef CONFIG_ROBOT_SERVO3
        else if (servo == 3) 
                GPIO_WRITE_LOW(CONFIG_ROBOT_SERVO3);
#endif
#ifdef CONFIG_ROBOT_SERVO4
        else if (servo == 4) 
                GPIO_WRITE_LOW(CONFIG_ROBOT_SERVO4);
#endif
}

/* Interrupt vectors */

static uint8_t index = 0;

ISR(TIMER1_OVF_vect)
{
        TCCR1B = 0; /* stop timer */
        if (!servo_ready) {
                servo_sort();
                servo_ready = 1;
        }

        /* Turn all GPIO on */
#ifdef CONFIG_ROBOT_SERVO1
        GPIO_WRITE_HIGH(CONFIG_ROBOT_SERVO1);
#endif
#ifdef CONFIG_ROBOT_SERVO2
        GPIO_WRITE_HIGH(CONFIG_ROBOT_SERVO2);
#endif
#ifdef CONFIG_ROBOT_SERVO3
        GPIO_WRITE_HIGH(CONFIG_ROBOT_SERVO3);
#endif
#ifdef CONFIG_ROBOT_SERVO4
        GPIO_WRITE_HIGH(CONFIG_ROBOT_SERVO4);
#endif

        index = 0;
        while (servo_queue[index].value == 0) {
                servo_off(servo_queue[index].i);
                index++;
        }

        /* this trick is required because TCNT1 could suddenly reach OCR1A */
        if (index < CONFIG_ROBOT_NUM_SERVO)
                OCR1A = servo_queue[index].value;
        else
                OCR1A = 12500;
        TCNT1 = 0;
        TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
        
}

ISR(TIMER1_COMPA_vect)
{
        TCCR1B = 0; /* stop timer */
        if (index == CONFIG_ROBOT_NUM_SERVO + 1) {
                TCNT1 = 65535;
                TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
                return;
        }
        
        uint16_t ocr = OCR1A;
        while (index < CONFIG_ROBOT_NUM_SERVO && servo_queue[index].value == ocr)
                servo_off(servo_queue[index++].i);
        
        if (index == CONFIG_ROBOT_NUM_SERVO) {
                OCR1A = 12500;
                index++;
        } else {
                OCR1A = servo_queue[index].value;
        }

        TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
}
