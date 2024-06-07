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

void forward(client_t *client, server_t *server)
{
    move(client->drone, server);
    send(client->socket, "ok\n", 3, 0);
}

void right(client_t *client, server_t *server)
{
    (void)server;
    turn(client->drone, RIGHT);
    send(client->socket, "ok\n", 3, 0);
}

void left(client_t *client, server_t *server)
{
    (void)server;
    turn(client->drone, LEFT);
    send(client->socket, "ok\n", 3, 0);
}

void fork_player(client_t *client, server_t *server)
{
    linked_list_egg_t *tmp = calloc(1, sizeof(linked_list_egg_t));

    if (tmp == NULL)
        return;
    tmp->egg = create_egg(client->drone->team_name, client->drone->x,
        client->drone->y);
    if (tmp->egg == NULL) {
        free(tmp);
        return;
    }
    tmp->next = server->game->egg_list;
    server->game->egg_list->prev = tmp;
    server->game->egg_list = tmp;
    for (int i = 0; i < server->info_game.nb_teams; i++) {
        if (server->game->teams[i].name == client->drone->team_name)
            server->game->teams[i].nb_egg++;
    }
    send(client->socket, "ok\n", 3, 0);
}
