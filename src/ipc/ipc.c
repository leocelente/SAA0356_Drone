#include "ipc.h"
#include <string.h>

// http://www.cse.yorku.ca/~oz/hash.html
static uint32_t hash(char *str) {
  uint32_t hash = 5381;
  char c = *str;
  while (c != '\0') {
    hash = ((hash << 5) + hash) + c;
    c = *str++;
  }
  return 4000 + (hash % 1000);
}

ipc_e_t ipc_init(ipc_node_t *node, int side, char *url) {
  printf("Initializing Sockets\r\n");
  int client_port = hash(url);
  int server_port = client_port + 1;

  if (side > 0) {
    server_port = hash(url);
    client_port = server_port + 1;
  }

  printf("Server: %d and Client: %d\r\n", server_port, client_port);

  int const server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket_fd == 0) {
    printf("Failed to Create to Server\r\n");
    return 3;
  }
  struct sockaddr_in server_address;
  int server_addrlen = sizeof(server_address);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(server_port);

  int const sb = bind(server_socket_fd, (struct sockaddr *)&server_address,
                      sizeof(server_address));
  if (sb < 0) {
    printf("Failed to Bind to Server (%d)\r\n", server_port);
    return 4;
  }

  node->server.fd = server_socket_fd;
  node->server.addrlen = server_addrlen;
  node->server.paddr = (struct sockaddr *)&server_address;
  node->client.port = client_port;
  node->server.port = server_port;

  printf("OK\r\n");
  return 0;
}

ipc_e_t ipc_listen(ipc_node_t *node, ipc_callback handler) {
  printf("Listenning... (%d)", node->server.fd);
  int const listening = listen(node->server.fd, 2);
  if (listening < 0) {
    printf("Failed  to LISTEN on socket\r\n");
    return 1;
  }
  while (true) {
    printf("...");
    int const sock_client =
        accept(node->server.fd, node->server.paddr, &node->server.addrlen);
    if (sock_client < 0) {
      printf("Socket ACCEPT failed (%d)\r\n", node->server.fd);
      return 2;
    }

    char buffer[IPC_MSG_SIZE] = {0};
    int valread = read(sock_client, buffer, IPC_MSG_SIZE);
    ipc_msg_t msg;
    memcpy(msg.data, buffer, sizeof(buffer));
    msg.size = valread;
    handler(&msg);
  }
  return 0;
}

ipc_e_t ipc_send(ipc_node_t *node, ipc_msg_t *msg) {

  printf("Sending [%d] to (%d)...\r\n", msg->size, node->client.fd);
  int const client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket_fd == 0) {
    printf("Failed to Create to Client\r\n");
    return 1;
  }
  struct sockaddr_in client_address;
  int client_addrlen = sizeof(client_address);
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(node->client.port);

  static bool first_time = true;
  if (first_time) {
    printf("This is the first message\r\n");
    node->client.addrlen = client_addrlen;
    node->client.paddr = (struct sockaddr *)&client_address;
    first_time = false;
  }

  int const cb = connect(client_socket_fd, (struct sockaddr *)&client_address,
                         sizeof(client_address));
  if (cb < 0) {
    printf("Failed to CONNECT to Client (%d)(%d)\r\n", cb, node->client.port);
    return 2;
  }
  node->client.fd = client_socket_fd;
  send(node->client.fd, msg->data, sizeof(msg->data), 0);
  return 0;
}
