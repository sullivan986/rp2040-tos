#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tos_k.h"

int utts = 0;

#define TASK1_STK_SIZE       1024
k_task_t task1;
k_stack_t task1_stack[TASK1_STK_SIZE];


#define TASK2_STK_SIZE       1024
k_task_t task2;
k_stack_t task2_stack[TASK2_STK_SIZE];

void task1_entry(void *arg)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while(1)
    {
        printf("core: 1 task: 1 LED OPEN\n");
        gpio_put(LED_PIN, 1);
        tos_task_delay(2000);
        printf("core: 1 task: 1 LED OFF\n");
        gpio_put(LED_PIN, 0);
        tos_task_delay(2000);
    }
}
void task2_entry(void *arg)
{
    while(1)
    {
        printf("core: 1 task: 2 count:%d \n", utts++);
        tos_task_delay(2500);
    }
}

void core1_main()
{
    while (1)
    {
        printf("core: 2 task: 0 push fifo count:%d \n", utts--);
        //multicore_fifo_push_blocking(count);
        sleep_ms(1000);
        //uint32_t g = multicore_fifo_pop_blocking();
        printf("core: 2 task: 0 pop  fifo count:%d \n", utts);
        sleep_ms(1000);
    }
}

int main()
{
    stdio_init_all();
    while (true) {
        sleep_ms(500);
        if (stdio_usb_connected()) {
            sleep_ms(250);
            printf("Press whatever to start main task:\n");
            getchar();
            break;
        }
    }
    multicore_launch_core1(core1_main);

    k_err_t  err1, err2;
    tos_knl_init();

    err1 = tos_task_create(
            &task1,
            "task1",
            task1_entry,
            NULL,
            2,
            task1_stack,
            1024,
            20
            );

    err2 = tos_task_create(
            &task2,
            "task2",
            task2_entry,
            NULL,
            3,
            task2_stack,
            1024,
            20
    );


    tos_knl_start();
    return 0;
}