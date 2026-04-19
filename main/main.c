#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stepper_uln2003.h"
#include "sdkconfig.h"

static stepper_t stepper;

// Wave drive
// static const uint8_t wave_seq[4][4] = {
//     {1,0,0,0},
//     {0,1,0,0},
//     {0,0,1,0},
//     {0,0,0,1}
// };

// Full-step (future)
// static const uint8_t full_seq[4][4] = {
//     {1,1,0,0},
//     {0,1,1,0},
//     {0,0,1,1},
//     {1,0,0,1}
// };

void app_main(void)
{
    printf("Stepper Test Starting...\n");

    stepper.pins[0] = CONFIG_GPIO_IN1_PIN;
    stepper.pins[1] = CONFIG_GPIO_IN2_PIN;
    stepper.pins[2] = CONFIG_GPIO_IN3_PIN;
    stepper.pins[3] = CONFIG_GPIO_IN4_PIN;

    stepper_init(&stepper);

    while (1) {
        printf("Forward...\n");
        stepper_step_n(&stepper, 128, 1, 3);  // ~1/4 rotation
        stepper_release(&stepper);

        vTaskDelay(pdMS_TO_TICKS(2000));

        printf("Backward...\n");
        stepper_step_n(&stepper, 128, -1, 3);
        stepper_release(&stepper);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    // while (1) {
    //     for (int i = 0; i < 4; i++) {
    //         printf("Testing pin %d\n", i);

    //         for (int j = 0; j < 4; j++) {
    //             gpio_set_level(stepper.pins[j], full_seq[i][j]);
    //         }

    //         vTaskDelay(pdMS_TO_TICKS(500));
    //     }
    // }
}