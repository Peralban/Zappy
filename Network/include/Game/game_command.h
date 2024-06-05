/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "game.h"
#include "game_functions.h"
#include <stdio.h>

void forward(client_t *client, server_t *server);
void right(client_t *client, server_t *server);
void left(client_t *client, server_t *server);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server);
    int duration;
} command_t;

static const command_t commands_opt[] = {
    {"Forward", &forward, 7},
    {"Right", &right, 7},
    {"Left", &left, 7},
    {NULL, NULL, 0}
};
