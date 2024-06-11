/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char **args);
    int nb_args;
} command_gui_t;

static const command_gui_t commands_gui[] = {
    {NULL, NULL, 0}
};