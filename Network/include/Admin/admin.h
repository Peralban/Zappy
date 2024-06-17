/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"

void exec_admin_commands(client_t *client, server_t *server, char *buffer);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char **args);
    int nb_args;
} command_admin_t;

static const command_admin_t commands_admin[] = {
    {NULL, NULL, 0}
};
