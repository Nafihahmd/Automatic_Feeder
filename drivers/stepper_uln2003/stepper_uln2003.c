/**
 * @file stepper_uln2003.c
 * @brief Implementation of ULN2003A stepper motor driver.
 */
#include "stepper_uln2003.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <rom/ets_sys.h>

// Wave drive
static const uint8_t wave_seq[4][4] = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1}
};

// Full-step (future)
static const uint8_t full_seq[4][4] = {
    {1,1,0,0},
    {0,1,1,0},
    {0,0,1,1},
    {1,0,0,1}
};

// Half-step (future)
static const uint8_t half_seq[8][4] = {
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1}
};

/* API Implementations */
void stepper_init(stepper_t *m)
{
    for (int i = 0; i < 4; i++) {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << m->pins[i]),
            .mode = GPIO_MODE_OUTPUT,
        };
        gpio_config(&io_conf);
        gpio_set_level(m->pins[i], 0);
    }

    m->step_index = 0;
    // m->mode = STEPPER_MODE_FULL;  // Default to full step
    m->mode = STEPPER_MODE_WAVE;  // Default to wave step
}

/**
 * @brief Apply a step pattern to GPIO pins.
 *
 * Sets the output level of each GPIO according to the given pattern.
 * A short delay is introduced to allow signal stabilization.
 *
 * @param[in] m Pointer to stepper handle
 * @param[in] pattern Array of 4 values representing coil states
 */
static void apply_step(stepper_t *m, const uint8_t *pattern)
{
    // printf("Applying step: [%d %d %d %d]\n", pattern[0], pattern[1], pattern[2], pattern[3]);
    for (int i = 0; i < 4; i++) {
        gpio_set_level(m->pins[i], pattern[i]);
    }
    // critical: allow signals to settle
    ets_delay_us(50);
}

void stepper_step(stepper_t *m, int direction)
{
    const uint8_t (*seq)[4];
    int seq_len;

    switch (m->mode) {
        case STEPPER_MODE_WAVE:
            seq = wave_seq;
            seq_len = 4;
            break;

        case STEPPER_MODE_FULL:
            seq = full_seq;
            seq_len = 4;
            break;

        case STEPPER_MODE_HALF:
            seq = half_seq;
            seq_len = 8;
            break;

        default:
            return;
    }

    m->step_index += direction;
    if (m->step_index < 0)
        m->step_index = seq_len - 1;
    else if (m->step_index >= seq_len)
        m->step_index = 0;

    apply_step(m, seq[m->step_index]);
}

void stepper_step_n(stepper_t *m, int steps, int direction, int delay_ms)
{
    for (int i = 0; i < steps; i++) {
        stepper_step(m, direction);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}

void stepper_release(stepper_t *m)
{
    for (int i = 0; i < 4; i++) {
        gpio_set_level(m->pins[i], 0);
    }
}