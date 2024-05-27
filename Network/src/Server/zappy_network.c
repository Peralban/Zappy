/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** server.c
*/

#include "Server/server.h"
#include <unistd.h>

static int check_error(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n");
        printf("\tport\tis the port number\n");
        printf("\twidth\tis the width of the world\n");
        printf("\theight\tis the height of the world\n");
        printf("\tnameX\tis the name of the team X\n");
        printf("\tclientsNb\tis the number of authorized clients per team\n");
        printf("\tfreq\tis the reciprocal of time unit for execution of actions\n");
        return 0;
    }
    return 1;
}

static void setup_server_address(server_t **server)
{
    (*server)->serverAddress->sin_family = AF_INET;
    (*server)->serverAddress->sin_addr.s_addr = htons(INADDR_ANY);
    (*server)->serverAddress->sin_port = htons((*server)->port);
    if (setsockopt((*server)->socket, SOL_SOCKET, SO_REUSEADDR,
    &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAIL);
    }
}

static void bind_and_listen(server_t *server)
{
    int listenStatus = 0;
    int bindStatus = bind(server->socket,
    (struct sockaddr *)server->serverAddress, sizeof(*server->serverAddress));

    check_return_value(bindStatus, BIND);
    listenStatus = listen(server->socket, 5);
    check_return_value(listenStatus, LISTEN);
}

int zappy_network(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));
    int check = check_error(ac, av);

    if (server == NULL || check == -1)
        return EXIT_FAIL;
    if (check == 0)
        return EXIT_SUCC;
    server->serverAddress = malloc(sizeof(struct sockaddr_in));
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    server->port = atoi(av[1]);
    check_return_value(server->socket, SOCKET);
    setup_server_address(&server);
    bind_and_listen(server);
    return server_loop(server);
}
