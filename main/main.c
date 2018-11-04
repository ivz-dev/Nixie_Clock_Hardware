#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "setDigit.h"

#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"

#define TIMER_INTR_SEL TIMER_INTR_LEVEL  /*!< Timer level interrupt */
#define TIMER_GROUP    TIMER_GROUP_0     /*!< Test on timer group 0 */
#define TIMER_DIVIDER   80               /*!< Hardware timer clock divider, 80 to get 1MHz clock to timer */
#define TIMER_SCALE    (TIMER_BASE_CLK / TIMER_DIVIDER)  /*!< used to calculate counter value */
#define TIMER_FINE_ADJ   (0*(TIMER_BASE_CLK / TIMER_DIVIDER)/1000000) /*!< used to compensate alarm value */
#define TIMER_INTERVAL0_SEC   (0.001)   /*!< test interval for timer 0 */

#define PIN_A 18
#define PIN_B 19
#define PIN_C 22
#define PIN_D 23

#define PIN_1 5
#define PIN_2 17
#define PIN_3 16
#define PIN_4 4

int h = 13;
int m = 10;

void gpioInit()
{
    gpio_set_direction(PIN_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_B, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_C, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_D, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_4, GPIO_MODE_OUTPUT);
}

void incrementH() {
    while (1) {
        for (int i=1; i<30; i++) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            m = i;
        }
    }
}


int cnt = 0;
int pins[4] = {5, 17, 16, 4};
int flag = 0;

void IRAM_ATTR timer_group0_isr(void *para){ // timer group 0, ISR
    int timer_idx = (int) para;
     uint32_t intr_status = TIMERG0.int_st_timers.val;
      if((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {

        TIMERG0.hw_timer[timer_idx].update = 1;
        TIMERG0.int_clr_timers.t0 = 1;
        TIMERG0.hw_timer[timer_idx].config.alarm_en = 1;

          if (flag == 0) {
            for (int i = 0; i<4; i++) {
                gpio_set_level(pins[i], 0);
                flag = 1;
            }
          } else {
                int digit1 = h / 10;
                int digit2 = h % 10;
                int digit3 = m / 10;
                int digit4 = m % 10;

                int numb[4] = {digit4, digit3, digit2, digit1};

                setDigit(numb[cnt]);
                gpio_set_level(pins[cnt], 1);
                flag = 0;
                cnt++;
                if (cnt == 4) cnt = 0;
          }
      }
}
static void example_tg0_timer0_init()
{
    int timer_group = TIMER_GROUP_0;
    int timer_idx = TIMER_0;
    timer_config_t config;
    config.alarm_en = 1;
    config.auto_reload = 1;
    config.counter_dir = TIMER_COUNT_UP;
    config.divider = TIMER_DIVIDER;
    config.intr_type = TIMER_INTR_SEL;
    config.counter_en = TIMER_PAUSE;
    /*Configure timer*/
    timer_init(timer_group, timer_idx, &config);
    /*Stop timer counter*/
    timer_pause(timer_group, timer_idx);
    /*Load counter value */
    timer_set_counter_value(timer_group, timer_idx, 0x00000000ULL);
    /*Set alarm value*/
    timer_set_alarm_value(timer_group, timer_idx, (TIMER_INTERVAL0_SEC * TIMER_SCALE) - TIMER_FINE_ADJ);
    /*Enable timer interrupt*/
    timer_enable_intr(timer_group, timer_idx);
    /*Set ISR handler*/
    timer_isr_register(timer_group, timer_idx, timer_group0_isr, (void*) timer_idx, ESP_INTR_FLAG_IRAM, NULL);
    /*Start timer counter*/
    timer_start(timer_group, timer_idx);
}

void app_main()
{
    gpioInit();
    xTaskCreate(&incrementH, "incrementH", 512, NULL, 5, NULL);
    example_tg0_timer0_init();
}