/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** server_loop.c
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include <stdio.h>

static void new_client(client_list_t **list, server_t *server)
{
    struct sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(server->socket,
    (struct sockaddr *) &client_address, &client_address_length);

    check_return_value(client_socket, ACCEPT);
    add_client_to_list(list, create_client(client_socket, &client_address));
    FD_SET(client_socket, &server->readfds);
    FD_SET(client_socket, &server->writefds);
}

static void recv_command(client_list_t *tmp, server_t **server)
{
    char buffer[1024];
    int buffer_length = 0;

    (void)server;
    buffer_length = recv(tmp->client->clientServer->socket, buffer, 1024, 0);
    check_return_value(buffer_length, RECV);
    buffer[buffer_length] = '\0';
    printf("Received: %s\n", buffer);
    send(tmp->client->clientServer->socket, buffer, buffer_length, 0);
}// the send is temporary, it will be deplaced in another function,

// server is not used for no, but it will be used in the future
static void client_already_connected(client_list_t **list, server_t **server)
{
    for (client_list_t *tmp = *list; tmp->client != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->client->clientServer->socket, &(*server)->readfds)) {
            recv_command(tmp, server);
        }
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
        FD_SET(tmp->client->clientServer->socket, &server->readfds);
        FD_SET(tmp->client->clientServer->socket, &server->writefds);
        if (tmp->client->clientServer->socket > *max_fd) {
            *max_fd = tmp->client->clientServer->socket;
        }
        if (tmp->next == NULL)
            break;
    }
}

int server_loop(server_t *server)
{
    client_list_t *list = create_client_list();
    int max_fd = server->socket;
    int select_status;

    while (1) {
        if (FD_ISSET(server->socket, &server->readfds))
            new_client(&list, server);
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        set_all_in_fd(server, list, &max_fd);
        select_status = select(max_fd + 1, &server->readfds, NULL, NULL, NULL);
        check_return_value(select_status, SELECT);
        client_already_connected(&list, &server);
    }
}
