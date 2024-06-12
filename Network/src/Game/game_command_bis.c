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
#include "GuiProtocol/gui_event.h"

void look(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    char *str = look_around(client->drone, server);

    send(client->socket, str, strlen(str), 0);
    free(str);
}

void inventory(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    char *str = display_inventory(client->drone);

    (void)server;
    send(client->socket, str, strlen(str), 0);
    free(str);
}

void broadcast(client_t *client, server_t *server, char **args)
{
    bool is_ok = launch_broadcast(client->drone, server, args[0]);
    void *data[2];

    send(client->socket, is_ok ? "ok\n" : "ko\n", 3, 0);
    ((client_t **)data)[0] = client;
    ((char **)data)[1] = args[0];
    gui_event(GUI_PBC, server, data);
}

void eject(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    bool player_hit = hit_players(client, server);
    bool egg_hit = hit_eggs(client, server);

    send(client->socket, (player_hit | egg_hit) ? "ok\n" : "ko\n", 3, 0);
    gui_event(GUI_PEX, server, client);
}
