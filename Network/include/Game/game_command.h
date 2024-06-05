/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "game.h"
#include <stdio.h>

void forward(drone_t *drone, server_t *server);

void right(drone_t *drone, server_t *server);

void left(drone_t *drone, server_t *server);

void look(drone_t *drone, server_t *server);

typedef struct {
    char *name;
    void (*function)(drone_t *drone, server_t *server);
} command_t;

static const command_t commands[] = {
    {"Forward", &forward},
    {"Right", &right},
    {"Left", &left},
    {"Look", &look},
};
