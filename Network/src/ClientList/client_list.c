/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** client_list.c
*/

#include "ClientList/client_list.h"

client_list_t *create_client_list(void)
{
    client_list_t *list = malloc(sizeof(client_list_t));

    list->client = NULL;
    list->next = NULL;
    list->prev = NULL;
    return (list);
}

client_t *create_client(int socket)
{
    client_t *client = calloc(1, sizeof(client_t));

    client->socket = socket;
    client->state = WAITING;
    return (client);
}

int add_client_to_list(client_list_t *list, client_t *client)
{
    client_list_t *tmp = list;

    if (list->client == NULL) {
        list->client = client;
        list->next = NULL;
        list->prev = NULL;
    } else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = malloc(sizeof(client_list_t));
        if (tmp->next == NULL)
            return -1;
        tmp->next->client = client;
        tmp->next->next = NULL;
        tmp->next->prev = tmp;
    }
    return 0;
}

static void remove_client_bis(client_list_t *tmp, client_t *client)
{
    while (tmp != NULL && tmp->client != client)
        tmp = tmp->next;
    if (tmp == NULL)
        return;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
}

void remove_client_from_list(client_list_t **list, client_t *client)
{
    client_list_t *tmp = *list;

    if (tmp != NULL && tmp->client == client) {
        if (tmp->next != NULL) {
            *list = tmp->next;
            (*list)->prev = NULL;
        } else {
            (*list)->next = NULL;
            (*list)->prev = NULL;
            (*list)->client = NULL;
        }
        return;
    }
    remove_client_bis(tmp, client);
}
