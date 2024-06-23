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

bool fork_condition(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    gui_pfk(server, client->drone->id);
    return true;
}

void fork_player(client_t *client, server_t *server,
    __attribute__((unused))char **args)
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
    gui_enw(server, client->drone, tmp->egg);
    tmp->next = server->game->egg_list;
    if (server->game->egg_list != NULL)
        server->game->egg_list->prev = tmp;
    server->game->egg_list = tmp;
    for (int i = 0; i < server->info_game.nb_teams; i++) {
        if (server->game->teams[i].name == client->drone->team_name)
            server->game->teams[i].nb_egg++;
    }
    send(client->socket, "ok\n", 3, 0);
}
