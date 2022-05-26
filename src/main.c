#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void task2(void *args __attribute((unused))) {
        for (;;) {
                gpio_toggle(GPIOC, GPIO13);
                vTaskDelay(pdMS_TO_TICKS(800));
        }
}

int main(void)
{
        rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

        rcc_periph_clock_enable(RCC_GPIOC);
        gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);

        xTaskCreate(task2,"LED1",100,NULL,configMAX_PRIORITIES-1,NULL);
        vTaskStartScheduler();
        for (;;);

        return 0;
}
