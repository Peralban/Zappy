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

void forward(drone_t *drone, server_t *server,
    __attribute__((unused))char *args)
{
    move(client->drone, server);
    send(client->socket, "ok\n", 3, 0);
}

void right(drone_t *drone, server_t *server,
    __attribute__((unused))char *args)
{
    (void)server;
    turn(client->drone, RIGHT);
    send(client->socket, "ok\n", 3, 0);
}

void left(drone_t *drone, server_t *server,
    __attribute__((unused))char *args)
{
    (void)server;
    turn(client->drone, LEFT);
    send(client->socket, "ok\n", 3, 0);
}

void look(drone_t *drone, server_t *server,
    __attribute__((unused))char *args)
{
    char *str = look_around(drone, server);

    free(str);
}

void inventory(drone_t *drone, server_t *server,
    __attribute__((unused))char *args)
{
    char *str = display_inventory(drone);

    (void)server;
    free(str);
}

void broadcast(drone_t *drone, server_t *server, char *args)
{
    launch_broadcast(drone, server, args);
}
