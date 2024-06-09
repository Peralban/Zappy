/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Game/game.h"
#include "Game/game_command.h"
#include "Game/game_functions.h"
#include "Server/server.h"

static bool count_players_on_tile_at_lvl(int x, int y, int lvl, server_t *server)
{
    int count = 0;
    linked_list_drone_t *tmp = server->game->map[x][y].drone_list;

    while (tmp != NULL) {
        if (tmp->drone->level == lvl)
            count++;
        tmp = tmp->next;
    }
    return count;
}

static bool check_incantation_prerequisites(client_t *client, server_t *server)
{
    if (client->drone->level > 7)
        return false;
    for (int i = 1; i < 7; i++) {
        if (server->game->map[client->drone->x][client->drone->y].inventory[i]
        < incantation_level_prerequisites[client->drone->level - 1][i])
            return false;
    }
    int count = count_players_on_tile_at_lvl(client->drone->x, client->drone->y,
        client->drone->level, server);
    if (count < incantation_level_prerequisites[client->drone->level - 1][0])
        return false;
    return true;
}

static void put_everyone_on_tile_to_incantation_lvl(int x, int y, int lvl, server_t *server)
{
    client_list_t *tmp = server->list;

    while (tmp != NULL) {
        if (tmp->client->drone->x == x && tmp->client->drone->y == y
        && tmp->client->drone->level == lvl) {
            //TODO: send to everyone on tile
        }
        tmp = tmp->next;
    }
}

bool check_incantation_condition(client_t *client, server_t *server)
{
    bool ret = check_incantation_prerequisites(client, server);

    if (ret == false) {
        send(client->socket, "ko\n", 3, 0);
        return false;
    } else {
        put_everyone_on_tile_to_incantation_lvl(client->drone->x, client->drone->y,
            client->drone->level, server);
        return true;
    }
}

void incantation(client_t *client, server_t *server)
{
    (void)server;
    send(client->socket, "ok\n", 3, 0);
}
