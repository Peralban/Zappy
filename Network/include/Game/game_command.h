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

void look(drone_t *drone, server_t *server);
void inventory(drone_t *drone, server_t *server);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server);
    int duration;
} command_t;

static const command_t commands[] = {
    {"Forward", &forward},
    {"Right", &right},
    {"Left", &left},
    {"Look", &look},
    {"Inventory", &inventory},
};
