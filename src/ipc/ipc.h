#pragma once
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define IPC_MSG_SIZE 255

// error
typedef enum { IPC_OK = 0, IPC_FAIL = 1 } ipc_e_t;

typedef enum { IPC_CLIENT, IPC_SERVER } ipc_role_t;

typedef struct {
  int size;
  uint8_t data[IPC_MSG_SIZE];
} ipc_msg_t;

typedef void (*ipc_callback)(ipc_msg_t const *);

typedef struct {
  int fd;
  struct sockaddr *paddr;
  uint32_t addrlen;
  int port;
} ipc_connection_t;

typedef struct {
  ipc_connection_t server;
  ipc_connection_t client;
} ipc_node_t;

ipc_e_t ipc_init(ipc_node_t *node, int side, char *url);
ipc_e_t ipc_listen(ipc_node_t *node, ipc_callback callback);
ipc_e_t ipc_send(ipc_node_t *node, ipc_msg_t *msg);
