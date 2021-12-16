#include "main.h"
#include "driver.h"
#include "ipc.h"
#include <stdio.h>

int pwm_test() { return ipc_test() + driver_test(); }

int main(void) { printf("PWM_test: %d,  expected 2", pwm_test()); }
