/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"


void map_size_cmd(client_t *client, server_t *server, char **args);
void one_tile_content(client_t *client, server_t *server, char **args);
void get_map_content(client_t *client, server_t *server, char **args);
void get_all_teams(client_t *client, server_t *server, char **args);
void get_player_position(client_t *client, server_t *server, char **args);
void get_player_level(client_t *client, server_t *server, char **args);
void get_player_inventory(client_t *client, server_t *server, char **args);
void time_request(client_t *client, server_t *server, char **args);
void time_modification(client_t *client, server_t *server, char **args);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char **args);
    int nb_args;
} command_gui_t;

static const command_gui_t commands_gui[] = {
    {"msz", map_size_cmd, 0},
    {"bct", one_tile_content, 2},
    {"mct", get_map_content, 0},
    {"tna", get_all_teams, 0},
    {"ppo", get_player_position, 1},
    {"plv", get_player_level, 1},
    {"pin", get_player_inventory, 1},
    {"sgt", time_request, 0},
    {"sst", time_modification, 1},
    {NULL, NULL, 0}
};
