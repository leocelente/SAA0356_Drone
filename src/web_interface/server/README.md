# Servidor HTTP de Comandos

Por meio deste módulo é possivel gerar uma API
com "endpoints" HTTP. Para cada endpoint associa-se 
um callback. 

Cada cliente deste servidor roda em uma thread reservada
para que o sistema se mantenha responsivo.

```c
endpoint_t api[] = {{"/motors", handle_motors},   //
                      {"/acquire", handle_acquire}, //
                      {"/release", handle_release}};

  int count = sizeof(api) / sizeof(api[0]);
  server_t server = {.port = 6644, .endpoint_count = count, .endpoints = api};

  server_init(&server);

  server_listen(&server);
```

