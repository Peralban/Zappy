/*
** EPITECH PROJECT, 2024
** admin_function.h
** File description:
** DESCRIPTION
*/

#pragma once

#include "Server/server.h"

void adm_level_up(client_t *client, server_t *server, char **args);

void adm_level_down(client_t *client, server_t *server, char **args);

void adm_set_level(client_t *client, server_t *server, char **args);

void adm_tp(client_t *client, server_t *server, char **args);

void adm_set_inventory(client_t *client, server_t *server, char **args);

void exec_admin_commands(client_t *client, server_t *server, char *buffer);

typedef struct admin_s {
    char *name;
    void (*function)(client_t *client, server_t *server, char **args);
    int nb_args;
} command_admin_t;

static command_admin_t commands_admin[] = {
    {"/levelup", adm_level_up, 1},
    {"/leveldown", adm_level_down, 1},
    {"/setlevel", adm_set_level, 2},
    {"/tp", adm_tp, 3},
    {"/setinventory", adm_set_inventory, 8},
    {NULL, NULL, 0}
};
