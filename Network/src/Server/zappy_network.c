/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** server.c
*/

#include "Server/server.h"
#include <unistd.h>
#include "Parsing/parse_args.h"
#include "ClientList/client_list.h"

static void setup_server_address(server_t *server)
{
    server->serverAddress->sin_family = AF_INET;
    server->serverAddress->sin_addr.s_addr = htons(INADDR_ANY);
    server->serverAddress->sin_port = htons(server->port);
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAIL);
    }
}

static void bind_and_listen(server_t *server)
{
    int listenStatus;
    int bindStatus = bind(server->socket,
    (struct sockaddr *)server->serverAddress, sizeof(*server->serverAddress));

    if (!check_return_value(bindStatus, BIND))
        exit(EXIT_FAIL);
    listenStatus = listen(server->socket, 5);
    if (!check_return_value(listenStatus, LISTEN))
        exit(EXIT_FAIL);
}

static void inthand(int signum)
{
    static int i = 0;

    (void)signum;
    replace_stop(1);
    if (i == 1) {
        printf("Server stopped\n");
        exit(0);
    }
    i++;
}

int zappy_network(char **args)
{
    server_t *server = move_args_to_server_struct(args);

    if (server == NULL)
        return EXIT_FAIL;
    server->serverAddress = malloc(sizeof(struct sockaddr_in));
    if (server->serverAddress == NULL)
        return EXIT_FAIL;
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!check_return_value(server->socket, SOCKET))
        return EXIT_FAIL;
    setup_server_address(server);
    bind_and_listen(server);
    server->list = create_client_list();
    signal(SIGINT, inthand);
    return server_loop(server);
}
