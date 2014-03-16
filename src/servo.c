#include <robot/servo.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <arch/antares.h>

#if defined(SERVO4_GPIO)
#define NUM_SERVO 4
#elif defined(SERVO3_GPIO)
#define NUM_SERVO 3
#elif defined(SERVO2_GPIO)
#define NUM_SERVO 2
#elif defined(SERVO1_GPIO)
#define NUM_SERVO 1
#else
#define NUM_SERVO 0
#endif

static void servo_sort(void);

static volatile struct servo_struct {
        volatile uint8_t i;
        volatile uint16_t value;
        volatile uint16_t next_value;
} servo_queue[NUM_SERVO];

static volatile uint8_t servo_ready = 0;

ANTARES_INIT_LOW(servo_init)
{
        /* init servo GPIO to out */
#ifdef SERVO1_GPIO
        GPIO_INIT_OUT(SERVO1_GPIO);
#endif
#ifdef SERVO2_GPIO
        GPIO_INIT_OUT(SERVO2_GPIO);
#endif
#ifdef SERVO3_GPIO
        GPIO_INIT_OUT(SERVO3_GPIO);
#endif
#ifdef SERVO4_GPIO
        GPIO_INIT_OUT(SERVO4_GPIO);
#endif

        /* init base timer */
        /* timer 1 for example */
        TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
        TIMSK1 |= (1<<TOIE1)|(1<<OCIE1A); /* one compare vector */

        /* clear base structure */
        for (uint8_t i=0; i<NUM_SERVO; i++) {
                servo_queue[i].i = i+1;
                servo_queue[i].value = 0;
                servo_queue[i].next_value = 65535;
        }

        servo_ready = 1;
}

void servo_write_us(uint8_t servo, uint16_t value)
{
        ANTARES_ATOMIC_BLOCK() {
                for (uint8_t i=0; i<NUM_SERVO; i++) {
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
        for (uint8_t i=0; i<NUM_SERVO; i++) {
                if (servo_queue[i].next_value != 65535) {
                        servo_queue[i].value = servo_queue[i].next_value;
                        servo_queue[i].next_value = 65535;
                }
        }

        for (uint8_t i=0; i<NUM_SERVO; i++) {
                for (uint8_t j=i+1; j<NUM_SERVO; j++) {
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
#ifdef SERVO1_GPIO
        if (servo == 1) 
                GPIO_WRITE_LOW(SERVO1_GPIO);
#endif
#ifdef SERVO2_GPIO
        else if (servo == 2) 
                GPIO_WRITE_LOW(SERVO2_GPIO);
#endif
#ifdef SERVO3_GPIO
        else if (servo == 3) 
                GPIO_WRITE_LOW(SERVO3_GPIO);
#endif
#ifdef SERVO4_GPIO
        else if (servo == 4) 
                GPIO_WRITE_LOW(SERVO4_GPIO);
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
        #ifdef SERVO1_GPIO
                GPIO_WRITE_HIGH(SERVO1_GPIO);
        #endif
        #ifdef SERVO2_GPIO
                GPIO_WRITE_HIGH(SERVO2_GPIO);
        #endif
        #ifdef SERVO3_GPIO
                GPIO_WRITE_HIGH(SERVO3_GPIO);
        #endif
        #ifdef SERVO4_GPIO
                GPIO_WRITE_HIGH(SERVO4_GPIO);
        #endif

        index = 0;
        while (servo_queue[index].value == 0) {
                servo_off(servo_queue[index].i);
                index++;
        }

        /* this trick is required because TCNT1 could suddenly reach OCR1A */
        if (index < NUM_SERVO)
                OCR1A = servo_queue[index].value;
        else
                OCR1A = 12500;
        TCNT1 = 0;
        TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
        
}

ISR(TIMER1_COMPA_vect)
{
        TCCR1B = 0; /* stop timer */
        if (index == NUM_SERVO + 1) {
                TCNT1 = 65535;
                TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
                return;
        }
        
        uint16_t ocr = OCR1A;
        while (index < NUM_SERVO && servo_queue[index].value == ocr)
                servo_off(servo_queue[index++].i);
        
        if (index == NUM_SERVO) {
                OCR1A = 12500;
                index++;
        } else {
                OCR1A = servo_queue[index].value;
        }

        TCCR1B = (1<<CS11)|(1<<CS10); /* f_cpu / 64 prescaler */
}
