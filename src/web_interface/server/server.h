#pragma once

#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define LINE_MAX 1024

// error
typedef enum { SERVER_OK = 0, SERVER_FAIL = 1 } server_e_t;

typedef enum { GET, POST, UNKN } method_t;

/* Function Pointer to Callback on Endpoint*/
typedef void (*endpoint_callback)(method_t method, char *body, char *response);
typedef struct {
  char const *name;
  endpoint_callback callback;
} endpoint_t;

typedef struct {
  char method[16];
  char body[256];
  char endpoint[32];
} request_t;

typedef struct {
  /* socket file descriptor */
  int fd;
  struct sockaddr_in addr;
  struct sockaddr *paddr;
  uint32_t addrlen;
} socket_t;

typedef struct {
  uint32_t port;
  uint32_t endpoint_count;
  // initialized on `server_init`
  socket_t _socket;
  endpoint_t *endpoints;
} server_t;

typedef struct {
  int sock_fd;
  server_t *pserver;
} handler_args_t;

/**
 * Initialize server
 *
 * `server`: pointer to server_t struct
 * @return server_e_t
 */
server_e_t server_init(server_t *server);

/**
 * Wait (blocking) for new client
 *
 * `server`: struct with parameters
 * @return server_e_t
 */
server_e_t server_listen(server_t *server);
