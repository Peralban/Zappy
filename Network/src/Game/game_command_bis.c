/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "Game/game.h"
#include "Game/game_command.h"
#include "Game/game_functions.h"
#include "Server/server.h"

static void eject_other(drone_t *other, drone_t *drone, server_t *server)
{
    char buffer[1024];
    int k[4] = {5, 7, 1, 3};

    move(other, server, drone->orientation);
    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp->client->drone == other) {
            sprintf(buffer, "eject: %d\n",
            k[(drone->orientation - tmp->client->drone->orientation + 4) % 4]);
            send(tmp->client->socket, buffer, strlen(buffer), 0);
            break;
        }
    }
}

void eject(client_t *client, server_t *server)
{
    bool hit = false;

    for (linked_list_drone_t *tmp = server->game->map[client->drone->x]
    [client->drone->y].drone_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->drone != client->drone) {
            eject_other(tmp->drone, client->drone, server);
            hit = true;
        }
    }
    for (linked_list_egg_t *tmp_egg = server->game->egg_list; tmp_egg != NULL;
    tmp_egg = tmp_egg->next) {
        if (tmp_egg->egg->x == client->drone->x &&
            tmp_egg->egg->y == client->drone->y) {
            remove_egg_elem(tmp_egg, &server->game->egg_list);
            hit = true;
        }
    }
    send(client->socket, hit ? "ok\n" : "ko\n", 3, 0);
}
