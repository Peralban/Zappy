/*
** EPITECH PROJECT, 2024
** game_command_bis.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Game/game_command.h"
#include "Game/game_functions.h"
#include "Server/server.h"

void broadcast(client_t *client, server_t *server, char *args)
{
    bool is_ok = launch_broadcast(client->drone, server, args);

    if (is_ok)
        send(client->socket, "ok\n", 3, 0);
    else
        send(client->socket, "ko\n", 3, 0);
}
