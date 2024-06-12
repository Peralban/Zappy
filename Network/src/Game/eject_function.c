/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Game/game.h"
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

static void decrease_egg_counter(server_t *server, linked_list_egg_t *tmp_egg)
{
    for (int i = 0; i < server->info_game.nb_teams; i++) {
        if (server->game->teams[i].name == tmp_egg->egg->team_name)
            server->game->teams[i].nb_egg--;
    }
}

bool hit_players(client_t *client, server_t *server)
{
    bool hit = false;
    linked_list_drone_t *tmp = server->game->map[client->drone->x]
    [client->drone->y].drone_list;

    while (tmp != NULL) {
        if (tmp->drone != client->drone) {
            hit = true;
            eject_other(tmp->drone, client->drone, server);
            tmp =
            server->game->map[client->drone->x][client->drone->y].drone_list;
        }
        tmp = tmp->next;
    }
    return hit;
}

bool hit_eggs(const client_t *client, server_t *server)
{
    bool hit = false;
    linked_list_egg_t *tmp_egg = server->game->egg_list;

    while (tmp_egg != NULL) {
        if (tmp_egg->egg->x == client->drone->x &&
            tmp_egg->egg->y == client->drone->y) {
            hit = true;
            decrease_egg_counter(server, tmp_egg);
            free(tmp_egg->egg);
            remove_egg_elem(tmp_egg, &server->game->egg_list);
            tmp_egg = server->game->egg_list;
            continue;
        }
        tmp_egg = tmp_egg->next;
    }
    return hit;
}
