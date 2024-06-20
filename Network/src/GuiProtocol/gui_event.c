/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void send_all_graphics(server_t *server, char *str)
{
    client_list_t *tmp = server->list;

    while (tmp != NULL) {
        if (tmp->client && tmp->client->state == GRAPHIC)
            send(tmp->client->socket, str, strlen(str), 0);
        tmp = tmp->next;
    }
}

void gui_pnw(server_t *server, drone_t *drone)
{
    char buffer[1024] = {0};

    sprintf(buffer, "pnw %d %d %d %d %d %s\n", drone->id,
    drone->x, drone->y, drone->orientation, drone->level, drone->team_name);
    send_all_graphics(server, buffer);
}
