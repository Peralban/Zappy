/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Server/server.h"

void start_gui_client(server_t *server, client_t *client)
{
    linked_list_egg_t *list = server->game->egg_list;
    char buffer[1024] = {0};

    if (client->state != GRAPHIC)
        return;
    while (list != NULL) {
        sprintf(buffer, "enw %d %d %d %d\n", list->egg->id, -1,
            list->egg->x, list->egg->y);
        send(client->socket, buffer, strlen(buffer), 0);
        list = list->next;
    }
}
