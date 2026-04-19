#pragma once
#include "driver/gpio.h"

typedef enum {
    STEPPER_MODE_WAVE = 0,
    STEPPER_MODE_FULL,
    STEPPER_MODE_HALF
} stepper_mode_t;

typedef struct {
    gpio_num_t pins[4];
    stepper_mode_t mode;
    int step_index;
} stepper_t;

void stepper_init(stepper_t *m);
void stepper_set_mode(stepper_t *m, stepper_mode_t mode);
void stepper_step(stepper_t *m, int direction);
void stepper_step_n(stepper_t *m, int steps, int direction, int delay_ms);
void stepper_release(stepper_t *m);