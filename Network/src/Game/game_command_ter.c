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

void set_object_down(client_t *client, server_t *server, char **args)
{
    bool is_ok = drop_object(client, server, args[0]);

    send(client->socket, is_ok ? "ok\n" : "ko\n", 3, 0);
}

void take_object_up(client_t *client, server_t *server, char **args)
{
    bool is_ok = take_object(client, server, args[0]);

    send(client->socket, is_ok ? "ok\n" : "ko\n", 3, 0);
}
