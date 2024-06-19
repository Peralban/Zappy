/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** client_list_bis.c
*/

#include "ClientList/client_list.h"

client_t *get_client_from_list(client_list_t *list, int socket)
{
    client_list_t *tmp = list;

    while (tmp != NULL && tmp->client != NULL) {
        if (tmp->client->socket == socket)
            return (tmp->client);
        tmp = tmp->next;
    }
    return NULL;
}

void eject_client_from_server(client_t *client, server_t *server)
{
    int return_value = close(client->socket);

    check_return_value(return_value, CLOSE);
    remove_client_from_list(&server->list, client);
    FD_CLR(client->socket, &server->readfds);
    FD_CLR(client->socket, &server->writefds);
    free(client);
}

void destroy_client_list(client_list_t *list)
{
    client_list_t *tmp = list;
    client_list_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        close(tmp->client->socket);
        free(tmp->client);
        free(tmp);
        tmp = next;
    }
}
