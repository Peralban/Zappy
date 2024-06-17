/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"

void exec_admin_commands(client_t *client, server_t *server, char *buffer);

void adm_pause(client_t *client, server_t *server, char **args);
void adm_set_freq(client_t *client, server_t *server, char **args);
void adm_tick(client_t *client, server_t *server, char **args);

void adm_level_up(client_t *client, server_t *server, char **args);
void adm_level_down(client_t *client, server_t *server, char **args);
void adm_set_level(client_t *client, server_t *server, char **args);

void adm_tp(client_t *client, server_t *server, char **args);

void adm_set_inventory(client_t *client, server_t *server, char **args);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char **args);
    int nb_args;
} command_admin_t;

static const command_admin_t commands_admin[] = {
    {"/pause", adm_pause, 0},
    {"/set_freq", adm_set_freq, 1},
    {"/tick", adm_tick, 2},
    {"/levelup", adm_level_up, 1},
    {"/leveldown", adm_level_down, 1},
    {"/setlevel", adm_set_level, 2},
    {"/tp", adm_tp, 3},
    {"/setinventory", adm_set_inventory, 8},
    {NULL, NULL, 0}
};

typedef struct {
    char type;
    char *type_str;
    int multiplier;
} tick_command_admin_t;

static const tick_command_admin_t tick_commands_admin[] = {
    {'s', "seconds", 1},
    {'t', "ticks", 0},
    {'m', "minutes", 60},
    {'h', "hours", 60 * 60},
    {'d', "days", 60 * 60 * 24},
    {0, NULL, 0}
};
