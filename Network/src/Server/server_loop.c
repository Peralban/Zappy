/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** server_loop.c
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include <stdio.h>

static void start_communication_with_client(int client_socket,
    info_game_t info_game, client_list_t *list, server_t *server)
{
    char buffer[1024];
    int buffer_length;

    sprintf(buffer, "WELCOME\n");
    send(client_socket, buffer, strlen(buffer), 0);
    buffer_length = recv(client_socket, buffer, 1024, 0);
    if (!check_return_value(buffer_length, RECV))
        return;
    buffer[buffer_length - 2] = '\0';
    for (int i = 0; info_game.team_names[i] != NULL; i++) {
        if (strcmp(buffer, info_game.team_names[i]) == 0) {
            sprintf(buffer, "%d\n%d %d\n",
                1, info_game.width, info_game.height);
            send(client_socket, buffer, strlen(buffer), 0);
            return;
        }
    }
    eject_client_from_server(
        get_client_from_list(list, client_socket), list, server);
}

static void new_client(client_list_t *list, server_t *server)
{
    struct sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(server->socket,
    (struct sockaddr *) &client_address, &client_address_length);

    if (!check_return_value(client_socket, ACCEPT))
        return;
    add_client_to_list(list, create_client(client_socket));
    FD_SET(client_socket, &server->readfds);
    FD_SET(client_socket, &server->writefds);
    start_communication_with_client(
        client_socket, server->info_game, list, server);
}

static void recv_command(client_list_t *tmp, server_t **server)
{
    char buffer[1024];
    int buffer_length = 0;

    (void)server;
    buffer_length = recv(tmp->client->socket, buffer, 1024, 0);
    if (!check_return_value(buffer_length, RECV))
        return;
    buffer[buffer_length] = '\0';
    printf("Received: %s\n", buffer);
    send(tmp->client->socket, buffer, buffer_length, 0);
}// the send is temporary, it will be deplaced in another function,

// server is not used for no, but it will be used in the future
static void client_already_connected(client_list_t *list, server_t **server)
{
    for (client_list_t *tmp = list; tmp->client != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->client->socket, &(*server)->readfds))
            recv_command(tmp, server);
        if (tmp->next == NULL || tmp->client == NULL)
            break;
    }
}

static void set_all_in_fd(server_t *server, client_list_t *list, int *max_fd)
{
    FD_SET(server->socket, &server->readfds);
    FD_SET(server->socket, &server->writefds);
    *max_fd = server->socket;
    for (client_list_t *tmp = list; tmp->client != NULL; tmp = tmp->next) {
        if (tmp->client == NULL)
            break;
        FD_SET(tmp->client->socket, &server->readfds);
        FD_SET(tmp->client->socket, &server->writefds);
        if (tmp->client->socket > *max_fd)
            *max_fd = tmp->client->socket;
        if (tmp->next == NULL)
            break;
    }
}

int server_loop(server_t *server)
{
    client_list_t *list = create_client_list();
    int max_fd = server->socket;
    int select_status;
    struct timeval timeout = {0, 0};

    while (1) {
        if (FD_ISSET(server->socket, &server->readfds))
            new_client(list, server);
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        set_all_in_fd(server, list, &max_fd);
        select_status = select(
            max_fd + 1, &server->readfds,NULL, NULL, &timeout);
        if (!check_return_value(select_status, SELECT))
            continue;
        client_already_connected(list, &server);
        // if time is up, do one game tick
    }
}
