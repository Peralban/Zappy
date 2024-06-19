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
#include "GuiProtocol/gui_event.h"

void forward(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    move(client->drone, server, client->drone->orientation);
    send(client->socket, "ok\n", 3, 0);
}

void right(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    (void)server;
    turn(client->drone, RIGHT);
    send(client->socket, "ok\n", 3, 0);
}

void left(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    (void)server;
    turn(client->drone, LEFT);
    send(client->socket, "ok\n", 3, 0);
}

void connect_nbr(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    char buffer[1024];

    for (int i = 0; i < server->info_game.nb_teams; i++) {
        if (server->game->teams[i].name == client->drone->team_name) {
            sprintf(buffer, "%d\n", server->game->teams[i].nb_egg);
            send(client->socket, buffer, strlen(buffer), 0);
            break;
        }
    }
}
