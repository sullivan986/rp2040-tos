#include "tos_k.h"


void SysTick_Handler(void)
{
    // refer to https://forums.raspberrypi.com/viewtopic.php?t=304201
    // sleep_us(123);
    if (tos_knl_is_running())
    {
        tos_knl_irq_enter();
        tos_tick_handler();
        tos_knl_irq_leave();
    }
}
