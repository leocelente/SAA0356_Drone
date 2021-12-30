#include "main.h"
#include "ipc.h"
#include "server.h"

// ipc client mutex

bool motor_flag = false;
pthread_mutex_t flag_lock;

void handle_motors(method_t method, char *body) {
  pthread_mutex_lock(&flag_lock);
  if (!motor_flag) {
    printf("Resource is already in use\r\n");
  } else {
    int m0, m1, m2, m3;
    sscanf(body, "[%d,%d,%d,%d]", &m0, &m1, &m2, &m3);
    printf("\r\nSetting Motors to: %d,%d,%d,%d\r\n", m0, m1, m2, m3);
  }
  pthread_mutex_unlock(&flag_lock);
}

void handle_acquire(method_t method, char *body) {
  pthread_mutex_lock(&flag_lock);
  if (!motor_flag) {
    motor_flag = true;
    printf("You now command the Resource\r\n");
  } else {
    printf("Resource is already in use\r\n");
  }
  pthread_mutex_unlock(&flag_lock);
}

void handle_release(method_t method, char *body) {
  pthread_mutex_lock(&flag_lock);
  if (motor_flag) {
    motor_flag = false;
    printf("You no longer command the Resource\r\n");
  } else {
    printf("Resource is already in free\r\n");
  }
  pthread_mutex_unlock(&flag_lock);
}

int main(int argc, char **argv) {
  printf("--Start Web Interface--\r\n");
  ipc_client_t ipc_client;
  // ipc_client_init(&ipc_client);
  ipc_connection_t conn;
  // ipc_client_connect(&conn);
  endpoint_t api[] = {{"/motors", handle_motors},   //
                      {"/acquire", handle_acquire}, //
                      {"/release", handle_release}};

  int const count = sizeof(api) / sizeof(api[0]);
  server_t server = {.port = 6644, .endpoint_count = count, .endpoints = api};

  server_init(&server);

  server_listen(&server);
}
