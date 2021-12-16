#include "main.h"
#include "ipc.h"
#include "main.h"
#include "server.h"
#include <pthread.h>
#include <stdio.h>

int web_test() { return ipc_test() + server_test(); }

int main(void) { printf("PWM_test: %d,  expected 2", web_test()); }
