#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define IPC_MSG_SIZE 255
#define LEFT_SOCKET_NAME "/tmp/left.sock"
#define RIGHT_SOCKET_NAME "/tmp/right.sock"

// error
typedef enum { IPC_OK = 0, IPC_FAIL = -1 } ipc_e_t;

typedef struct {
  int size;
  uint8_t data[IPC_MSG_SIZE];
} ipc_msg_t;

typedef struct {
  /* socket file descritor*/
  int fd;
  /* socket address struct */
  struct sockaddr_un addr;
  /* pointer to `addr`*/
  struct sockaddr *paddr;
  /* length of `addr`*/
  uint32_t addrlen;
  /* name of the domain socket */
  char *path;
} ipc_connection_t;

typedef struct {
  /* input connection,
    acts as server listening for clients */
  ipc_connection_t in;
  /* output connection,
      acts as socket client */
  ipc_connection_t out;
} ipc_node_t;

/**
 * Initializes IPC Node
 *
 * `node`: pointer to node struct
 * `side`: 0 or 1, sibling node must be other
 * @return ipc_e_t error
 */
ipc_e_t ipc_init(ipc_node_t *node, int side);

/**
 * Blocking Received from other IPC node
 *
 * `node`: pointer to node
 * `msg`: pointer to IPC message, to be filled
 * @return ipc_e_t error
 */
ipc_e_t ipc_recv(ipc_node_t *node, ipc_msg_t *msg);

/**
 * Send IPC Message to other node
 *
 * `node`: pointer to node
 * `msg`: message to be sent
 * @return ipc_e_t error
 */
ipc_e_t ipc_send(ipc_node_t *node, ipc_msg_t const *msg);
