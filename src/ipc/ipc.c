/**
 * @file ipc.c
 * @author Leonardo Celente (@leocelente)
 *
 * @version 0.1
 * @date 2022-01-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ipc.h"

ipc_e_t ipc_init(ipc_node_t *node, int side) {
  node->out.path = !(side > 0) ? LEFT_SOCKET_NAME : RIGHT_SOCKET_NAME;
  node->in.path = !(side > 0) ? RIGHT_SOCKET_NAME : LEFT_SOCKET_NAME;

  printf("Input Socket: %s\r\nOutput Socket: %s\r\n", node->in.path,
         node->out.path);

  // In case of forced termination, reset socket before re-creation
  unlink(node->in.path);

  int in_sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (in_sock_fd < 0) {
    perror("socket (input)");
    return -3;
  }
  node->in.fd = in_sock_fd;

  node->in.paddr = (struct sockaddr *)&node->in.addr;
  node->in.addrlen = sizeof(node->in.addr);
  node->in.addr.sun_family = AF_UNIX;
  strncpy(node->in.addr.sun_path, node->in.path,
          sizeof(node->in.addr.sun_path) - 1);

  int binded = bind(node->in.fd, node->in.paddr, node->in.addrlen);
  if (binded < 0) {
    perror("bind (input)");
    return -4;
  }

  int listening = listen(node->in.fd, 2);
  if (listening < 0) {
    perror("listen (input)");
    return -1;
  }
  return 0;
}

ipc_e_t ipc_recv(ipc_node_t *node, ipc_msg_t *msg) {
  int sock_client = accept(node->in.fd, node->in.paddr, &node->in.addrlen);
  if (sock_client < 0) {
    perror("accept (input)");
    return -2;
  }

  char buffer[IPC_MSG_SIZE] = {0};
  int valread = recv(sock_client, buffer, IPC_MSG_SIZE, 0);
  memcpy(msg->data, buffer, sizeof(buffer));
  msg->size = valread;
  return 0;
}

ipc_e_t ipc_send(ipc_node_t *node, ipc_msg_t const *msg) {
  int out_sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (out_sock_fd < 0) {
    perror("socket (output)");
    return -1;
  }
  node->out.fd = out_sock_fd;

  // write data in struct for easier debugging
  node->out.paddr = (struct sockaddr *)&node->out.addr;
  node->out.addrlen = sizeof(node->out.addr);
  node->out.addr.sun_family = AF_UNIX;
  strncpy(node->out.addr.sun_path, node->out.path,
          sizeof(node->out.addr.sun_path) - 1);

  int connected = connect(node->out.fd, node->out.paddr, node->out.addrlen);
  if (connected < 0) {
    perror("connect (output)");
    return -3;
  }

  send(node->out.fd, msg->data, sizeof(msg->data), 0);
  close(node->out.fd);
  return 0;
}
