#include "main.h"
#include "ipc.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

// ipc client mutex

bool motor_flag = false;
int key = 0;
pthread_mutex_t flag_lock;
int m0, m1, m2, m3;
ipc_node_t node;

static void handle_motors(method_t method, char *body, char *response) {
  pthread_mutex_lock(&flag_lock);
  if (method == POST) {
    if (!motor_flag) {
    } else {
      sscanf(body, "[%d,%d,%d,%d]", &m0, &m1, &m2, &m3);
      char values[] = "OK";
      strncpy(response, values, sizeof(values));

      float a[] = {m0, m1, m2, m3};
      ipc_msg_t msg = {.size = sizeof(a), .data = {0}};
      memcpy(msg.data, a, sizeof(a));
      printf("Sending to motors\r\n");
      ipc_send(&node, &msg);
    }

  } else if (method == GET) {
    char values[24] = {0};
    sprintf(values, "[%d,%d,%d,%d]", m0, m1, m2, m3);
    strncpy(response, values, sizeof(values));
  }
  pthread_mutex_unlock(&flag_lock);
}

static void handle_acquire(method_t method, char *body, char *response) {
  pthread_mutex_lock(&flag_lock);
  if (method == GET) {
    printf("FLAG: %d\r\n", motor_flag);
    if (!motor_flag) {

      motor_flag = true;
      char values[] = "OK";
      strncpy(response, values, sizeof(values));
    } else {
      char values[] = "FAIL";
      strncpy(response, values, sizeof(values));
    }
  } else if (method == POST) {
    char values[2] = {0};
    sprintf(values, "%d", motor_flag);
    strncpy(response, values, sizeof(values));
  }
  pthread_mutex_unlock(&flag_lock);
  printf("[%s]\r\n", response);
}

static void handle_release(method_t method, char *body, char *response) {
  pthread_mutex_lock(&flag_lock);
  if (method == GET) {
    if (motor_flag) {
      motor_flag = false;
      // printf("You no longer command the Resource\r\n");
      char values[] = "OK";
      strncpy(response, values, sizeof(values));
    } else {
      // printf("Resource is already in free\r\n");
      char values[] = "FAIL";
      strncpy(response, values, sizeof(values));
    }
  } else if (method == POST) {
  }
  pthread_mutex_unlock(&flag_lock);
}

int main(int argc, char **argv) {
  printf("--Start Web Interface--\r\n");

  ipc_init(&node, 1, "web::motors");

  endpoint_t api[] = {{"/motors", handle_motors},   //
                      {"/acquire", handle_acquire}, //
                      {"/release", handle_release}};

  int const count = sizeof(api) / sizeof(api[0]);
  server_t server = {.port = 6644, .endpoint_count = count, .endpoints = api};

  server_init(&server);

  server_listen(&server);
}
