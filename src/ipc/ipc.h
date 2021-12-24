#pragma once
#include <netinet/in.h>
#include <sys/socket.h>

#define IPC_MSG_SIZE 255

// error
typedef enum { IPC_OK = 0, IPC_FAIL = 1 } ipc_e_t;

typedef enum { IPC_CLIENT, IPC_SERVER } ipc_source_t;
typedef struct {
  ipc_source_t source;
  uint8_t data[IPC_MSG_SIZE];
} ipc_msg_t;

typedef struct {
} ipc_connection_t;

typedef void (*ipc_callback)(ipc_msg_t const *);
typedef struct {
  ipc_connection_t connection;
} ipc_client_t;

typedef struct {
  ipc_callback callback;
  ipc_connection_t connection;
} ipc_server_t;

ipc_e_t ipc_client_init(ipc_client_t *client, ipc_connection_t *connection);

ipc_e_t ipc_server_init(ipc_server_t *server);

ipc_e_t ipc_client_send(ipc_client_t *client, ipc_msg_t const *message);

ipc_e_t ipc_server_send(ipc_server_t *server, ipc_msg_t const *message);

ipc_e_t ipc_server_listen(ipc_server_t *server, ipc_connection_t *connection,
                          ipc_callback callback);
