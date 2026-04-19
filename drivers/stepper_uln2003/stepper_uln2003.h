/**
 * @file stepper_uln2003.h
 * @brief Driver for controlling 28BYJ-48 stepper motor using ULN2003A.
 *
 * This driver supports multiple stepping modes:
 * - Wave drive (single-phase)
 * - Full-step (two-phase)
 * - Half-step (mixed)
 *
 * Currently optimized for simple blocking control. Can be extended
 * for non-blocking operation using FreeRTOS tasks.
 */
#pragma once
#include "driver/gpio.h"

/** 
 * @brief Stepper motor modes 
 */
typedef enum {
    STEPPER_MODE_WAVE = 0,  /*!< Single-phase drive (low torque) */
    STEPPER_MODE_FULL,      /*!< Two-phase drive (higher torque) */
    STEPPER_MODE_HALF       /*!< Half-step drive (higher resolution) */
} stepper_mode_t;

/** 
 * @brief Stepper motor control structure 
 */
typedef struct {
    gpio_num_t pins[4];     /* GPIO pins connected to IN1, IN2, IN3, IN4 of ULN2003A */
    stepper_mode_t mode;    /* Current stepping mode */
    int step_index;         /* Current step index (0-3 for wave/full, 0-7 for half) */
} stepper_t;

/**
 * @brief Initialize the stepper motor driver.
 *
 * Configures GPIO pins as outputs and sets initial state to LOW.
 *
 * @param[in,out] m Pointer to stepper handle
 */
void stepper_init(stepper_t *m);

/**
 * @brief Set the stepping mode.
 *
 * Allows switching between wave, full-step, and half-step modes.
 *
 * @param[in,out] m Pointer to stepper handle
 * @param[in] mode Desired stepping mode
 */
void stepper_set_mode(stepper_t *m, stepper_mode_t mode);

/**
 * @brief Perform a single step.
 *
 * Advances the motor by one step in the specified direction.
 *
 * @param[in,out] m Pointer to stepper handle
 * @param[in] direction Direction of rotation
 *                      +1 for forward, -1 for reverse
 */
void stepper_step(stepper_t *m, int direction);

/**
 * @brief Rotate the motor by a number of steps (blocking).
 *
 * Executes multiple steps with a fixed delay between each step.
 *
 * @param[in,out] m Pointer to stepper handle
 * @param[in] steps Number of steps to move
 * @param[in] direction Direction (+1 or -1)
 * @param[in] delay_ms Delay between steps in milliseconds
 */
void stepper_step_n(stepper_t *m, int steps, int direction, int delay_ms);

/**
 * @brief Release the motor (disable all coils).
 *
 * Sets all GPIO outputs to LOW, reducing power consumption
 * and allowing the motor to rotate freely.
 *
 * @param[in,out] m Pointer to stepper handle
 */
void stepper_release(stepper_t *m);