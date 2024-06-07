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

void forward(client_t *client, server_t *server,
    __attribute__((unused))char *args)
{
    move(client->drone, server);
    send(client->socket, "ok\n", 3, 0);
}

void right(client_t *client, server_t *server,
    __attribute__((unused))char *args)
{
    (void)server;
    turn(client->drone, RIGHT);
    send(client->socket, "ok\n", 3, 0);
}

void left(client_t *client, server_t *server,
    __attribute__((unused))char *args)
{
    (void)server;
    turn(client->drone, LEFT);
    send(client->socket, "ok\n", 3, 0);
}

void look(client_t *client, server_t *server,
    __attribute__((unused))char *args)
{
    char *str = look_around(client->drone, server);

    send(client->socket, str, strlen(str), 0);
    free(str);
}

void inventory(client_t *client, server_t *server,
    __attribute__((unused))char *args)
{
    char *str = display_inventory(client->drone);

    (void)server;
    send(client->socket, str, strlen(str), 0);
    free(str);
}
