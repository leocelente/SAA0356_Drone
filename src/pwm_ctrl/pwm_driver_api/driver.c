/**
 * @file driver.c
 * @author Leonardo Celente (@leocelente)
 *
 * @version 0.1
 * @date 2021-12-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "driver.h"
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

pwm_e_t pwm_init(pwm_channel_t *channel, char const *path,
                 duty_cycle_t duty_cycle, period_t period) {

  if (duty_cycle < 0.f || duty_cycle > 100.f) {
    printf("Duty Cycle must be 0...100\n");
    return PWM_FAIL;
  }

  if (period < 0) {
    printf("Period must be positive!\n");
    return PWM_FAIL;
  }
  channel->path = path;
  pwm_set_period(channel, period);
  channel->period = period;
  pwm_set_duty_cycle(channel, duty_cycle);
  channel->duty_cycle = duty_cycle;
  return 0;
}

pwm_e_t pwm_set_duty_cycle(pwm_channel_t *channel, duty_cycle_t duty_cycle) {
  char path[PATH_SIZE] = {0};
  strcpy(path, channel->path);
  strcat(path, "/duty_cycle");
  int d = open(path, O_RDWR);
  if (d < 0) {
    perror("open");
    return 1;
  }

  float const one_ms = 1e6f;    // ns
  float x = duty_cycle / 100.f; // 0.00...1.00
  uint32_t dt_ns = one_ms + (x) * (one_ms);
  char buffer[24] = {0};
  sprintf(buffer, "%d", dt_ns);
  if (write(d, buffer, strlen(buffer)) < 0) {
    close(d);
    perror("write");
    return 2;
  }
  channel->duty_cycle = duty_cycle;
  close(d);
  printf("%s = %d ns\r\n", path, dt_ns);
  return 0;
}

pwm_e_t pwm_set_period(pwm_channel_t *channel, period_t period) {
  char path[PATH_SIZE];
  strcpy(path, channel->path);
  strcat(path, "/period");
  int d = open(path, O_RDWR);
  if (d < 0) {
    perror("open");
    return 1;
  }
  uint32_t period_ns = period * 1000 * 1000;
  char buffer[24] = {0};
  sprintf(buffer, "%d", period_ns);
  if (write(d, buffer, strlen(buffer)) < 0) {
    close(d);
    perror("write");
    return 2;
  }
  channel->period = period;
  close(d);
  printf("%s = %d ns\r\n", path, period_ns);
  return 0;
}

pwm_e_t pwm_enable(pwm_channel_t *channel) {
  // TODO: implement
  return 1;
}

pwm_e_t pwm_disable(pwm_channel_t *channel) {
  // TODO: implement
  return 1;
}
