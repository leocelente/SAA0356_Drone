#pragma once
#include <stdbool.h>
#include <stdint.h>
#define PATH_SIZE 1024
typedef float duty_cycle_t;
typedef uint32_t period_t;
typedef int file_descriptor_t;

// Error type
typedef enum { PWM_OK = 0, PWM_FAIL = 1 } pwm_e_t;

typedef struct {
  duty_cycle_t duty_cycle;
  period_t period;
  bool enabled;
  char const *path;
} pwm_channel_t;

typedef struct {
  uint8_t chip;
  uint8_t channel;
} fs_structure_t;

/**
    Changes channel duty cycle to given _percentage_
    `channel`: PWM Channel
    `duty`:_cycle Percentage duty cycle
    @return error
*/
pwm_e_t pwm_set_duty_cycle(pwm_channel_t *channel, duty_cycle_t duty_cycle);

/**
    Changes PWM channel period
    `channel`: PWM Channel
    `period`: Period time in milliseconds
    @return error
*/
pwm_e_t pwm_set_period(pwm_channel_t *channel, period_t period);

pwm_e_t pwm_enable(pwm_channel_t *channel);
pwm_e_t pwm_disable(pwm_channel_t *channel);

/**
 *  Initializes PWM channel in `path` with `duty_cycle` and
 `period`
 *
 * `channel`:
 * `path`: to sysfs char device
 * `duty`:_cycle in percent
 * `period`: in milliseconds
 * @return pwm_e_t error
 */
pwm_e_t pwm_init(pwm_channel_t *channel, char const *path,
                 duty_cycle_t duty_cycle, period_t period);
