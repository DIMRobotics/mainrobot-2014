#include <robot/odetect.h>
#include <robot/uart.h>

#include <lib/cerebellum/chassis.h>

static volatile uint8_t _state = 0;

void odetect_set_limit(odetect_dir_t dir, uint8_t value)
{
        uart_send('l');
        for (uint8_t i=0; i<6; i++) {
                if (dir & (1<<i))
                        uart_send(value);
                else
                        uart_send(255);
        }
}

void odetect_set_single_limit(odetect_dir_t dir, uint8_t value)
{
        uart_send('l');
        for (uint8_t i=0; i<6; i++) {
                if ((1<<i) & dir)
                        uart_send(value);
                else
                        uart_send(0);
        }
}

uint8_t odetect_get_state(odetect_dir_t dir)
{
        return (_state & dir) != 0;
}

void odetect_write_state(odetect_dir_t dir, uint8_t st)
{
        if (st)
                _state |= (1<<dir);
        else
                _state &= ~(1<<dir);
}

void odetect_interrupt(void)
{
        if (_state != 0)
                chassis_pause();
        else
                chassis_resume();
}
