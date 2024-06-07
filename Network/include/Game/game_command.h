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

void forward(client_t *client, server_t *server, char *args);

void right(client_t *client, server_t *server, char *args);

void left(client_t *client, server_t *server, char *args);

void look(client_t *client, server_t *server, char *args);

void inventory(client_t *client, server_t *server, char *args);

void broadcast(client_t *client, server_t *server, char *args);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char *arg);
    int duration;
    int nb_args;
} command_t;

static const command_t commands_opt[] = {
    {"Forward", &forward, 7, 0},
    {"Right", &right, 7, 0},
    {"Left", &left, 7, 0},
    {"Look", &look, 7, 0},
    {"Inventory", &inventory, 1, 0},
    {"Broadcast", &broadcast, 7, 1},
    {NULL, NULL, 0, 0}
};
