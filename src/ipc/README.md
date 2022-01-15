# Biblioteca IPC

É o componente responsável por passar comandos validados
pelo servidor HTTP para o processo do controlador de PWM. 

Utiliza de Unix Domain Sockets para construir uma linha
de comunicação bidirecional entre os dois nós.

```c
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
```
