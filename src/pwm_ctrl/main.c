/**
 * @file main.c
 * @author Leonardo Celente (@leocelente)
 *
 * @version 0.1
 * @date 2021-12-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "main.h"
#include "ini.h"
#include "ipc.h"
#include <string.h>

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

/**
 *  Global configuration with PWM sysfs drivers path
 */
config_t configuration;
ipc_node_t ipc;
pwm_channel_t ch0, ch1, ch2, ch3;

/**
 *  Called from INIH library, to parse parameters
 *
 * `config`: pointer to configuration
 * `section`: .ini current section
 * `name`: .parameter name
 * `value`: parameter value
 * @return int is valid
 */
static int parser(void *config, const char *section, const char *name,
                  const char *value) {
  config_t *pconfig = (config_t *)config;
  printf("Trying to match parameter: %s:%s of value: %s\r\n", section, name,
         value);

  if (MATCH("motor0", "path")) {
    strcpy(pconfig->channel0, value);
  } else if (MATCH("motor1", "path")) {
    strcpy(pconfig->channel1, value);
  } else if (MATCH("motor2", "path")) {
    strcpy(pconfig->channel2, value);
  } else if (MATCH("motor3", "path")) {
    strcpy(pconfig->channel3, value);
  } else {
    printf("Invalid parameter!  %s\r\n", name);
    return 0;
  }
  return 1;
}

/**
 *  Calls INIH parser and sets global configuration
 *
 * `config`:_path path to configuration ini file
 * @return true OK
 * @return false failed
 */
static bool read_config(char const *config_path) {
  config_t cfg = {0};
  if (ini_parse(config_path, parser, &cfg)) {
    return false;
  }
  memcpy(&configuration, &cfg, sizeof(config_t));
  return true;
}

/**
 *  Converts from a desired speed to a PWM duty cycle
 *
 * `speed`: in rpm
 * @return float duty_cycle in percent
 */
static float speed_to_dutycycle(float speed) {
  // ? Should we set a min/max rpm in config to use in this
  //?  conversion?
  return speed;
}

/**
 *  Called from IPC (only once) when the client sends commands
 *
 * `message`: data received from client
 */
void handle_client(ipc_msg_t const *message) {

  printf("Received a Message from Client!\r\n");
  input_t in = {0};
  memcpy(in.raw, message->data, sizeof(in.raw));
  printf("Set motors to: %f, %f, %f, %f\r\n", in.cmd.motor0, in.cmd.motor1,
         in.cmd.motor2, in.cmd.motor3);

  //? Should we disable the channels prior a reactivate them later to achieve
  //? sync?
  pwm_set_duty_cycle(&ch0, speed_to_dutycycle(in.cmd.motor0));
  pwm_set_duty_cycle(&ch1, speed_to_dutycycle(in.cmd.motor1));
  pwm_set_duty_cycle(&ch2, speed_to_dutycycle(in.cmd.motor2));
  pwm_set_duty_cycle(&ch3, speed_to_dutycycle(in.cmd.motor3));
}

int main(int argc, char **argv) {
  printf("--Starting Motor Controller--\r\n");
  printf("Checking config\r\n");

  if (!read_config(argv[1])) {
    printf("Failed to apply config!\r\n");
    return -1;
  }

  // Initialize motors
  printf("Initializing motors\r\n");
  pwm_init(&ch0, configuration.channel0, 0, MOTOR_PWM_PERIOD);
  pwm_init(&ch1, configuration.channel1, 0, MOTOR_PWM_PERIOD);
  pwm_init(&ch2, configuration.channel2, 0, MOTOR_PWM_PERIOD);
  pwm_init(&ch3, configuration.channel3, 0, MOTOR_PWM_PERIOD);

  // initialize server
  printf("Initializing Server\r\n");

  ipc_init(&ipc, 0, "web::motors");

  printf("Listening to clients...\r\n");

  ipc_msg_t msg;
  ipc_listen(&ipc, handle_client);
  printf("Calling Handle Client..\r\n");

  // {
  //   printf("Running simulated Command\r\n");
  //   command_t test = {.motor0 = 0.1, .motor1 = 1, .motor2 = 10, .motor3 =
  //   100}; input_t out = {.cmd = test}; ipc_msg_t msg; memcpy(msg.data,
  //   out.raw, sizeof(out.raw)); handle_client(&msg);
  // }

  printf("Closing Motor Controller!\r\n");
  return 0;
}
