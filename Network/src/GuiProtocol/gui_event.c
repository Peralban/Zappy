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
        if (tmp->client->state == GRAPHIC)
            send(tmp->client->socket, str, strlen(str), 0);
        tmp = tmp->next;
    }
}

void gui_event(event_type_e event, server_t *server, void *data)
{
    for (int i = 0; event_gui[i].event_type != 0; i++) {
        if (event_gui[i].event_type == event) {
            event_gui[i].function(server, data);
            return;
        }
    }
    printf("Unknown event\n");
}

void suc(__attribute__((unused))server_t *server, void *data)
{
    client_t *client = (client_t *)data;

    send(client->socket, "suc\n", 4, 0);
}

void pnw(server_t *server, void *data)
{
    client_t *client = (client_t *)data;
    char buffer[1024] = {0};

    sprintf(buffer, "pnw %d %d %d %d %d %s\n", client->drone->id,
    client->drone->x, client->drone->y, client->drone->orientation,
    client->drone->level, client->drone->team_name);
    send_all_graphics(server, buffer);
}
