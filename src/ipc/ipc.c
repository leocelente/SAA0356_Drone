#include "ipc.h"

ipc_e_t ipc_client_init(ipc_client_t *client, ipc_connection_t *connection) {}

ipc_e_t ipc_server_init(ipc_server_t *server) {}

ipc_e_t ipc_client_send(ipc_client_t *client, ipc_msg_t const *message) {}

ipc_e_t ipc_server_send(ipc_server_t *server, ipc_msg_t const *message) {}

ipc_e_t ipc_server_listen(ipc_server_t *server, ipc_connection_t *connection,
                          ipc_callback callback) {}
