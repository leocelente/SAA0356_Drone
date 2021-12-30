#pragma once

#include "driver.h"
#include "ini.h"
#include "ipc.h"
#include <stdio.h>
#include <string.h>
#define PATH_SIZE 1024
#define MOTOR_PWM_PERIOD 20
typedef struct {
  float motor0, motor1, motor2, motor3;
} command_t;

typedef union {
  command_t cmd;
  uint8_t raw[sizeof(command_t)];
} input_t;

typedef struct {
  char channel0[PATH_SIZE];
  char channel1[PATH_SIZE];
  char channel2[PATH_SIZE];
  char channel3[PATH_SIZE];
} config_t;
