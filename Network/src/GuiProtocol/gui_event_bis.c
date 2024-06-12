/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void pex(server_t *server, void *data)
{
    drone_t *drone = (drone_t *)data;
    char buffer[1024] = {0};

    sprintf(buffer, "pex %d\n", drone->id);
    send_all_graphics(server, buffer);
}

void pbc(server_t *server, void *data)
{
    drone_t *drone = ((drone_t **)data)[0];
    char *msg = ((char **)data)[1];
    char buffer[1024] = {0};

    sprintf(buffer, "pbc %d %s\n", drone->id, msg);
    send_all_graphics(server, buffer);
}

void pic(server_t *server, void *data)
{
    drone_t *drone = (drone_t *)data;
    char buffer[1024] = {0};

    sprintf(buffer, "pic %d %d %d", drone->x, drone->y,
        drone->level);
    for (linked_list_drone_t *tmp =
    server->game->map[drone->x][drone->y].drone_list;
    tmp != NULL; tmp = tmp->next) {
        if (tmp->drone->level == drone->level) {
            sprintf(buffer + strlen(buffer), " %d", tmp->drone->id);
        }
    }
    buffer[strlen(buffer)] = '\n';
    send_all_graphics(server, buffer);
}

void pie(server_t *server, void *data)
{
    drone_t *drone = (drone_t *)data;
    char buffer[1024] = {0};

    sprintf(buffer, "pie %d %d %d\n", drone->x, drone->y, drone->level);
    send_all_graphics(server, buffer);
}
