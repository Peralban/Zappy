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

void forward(drone_t *drone, server_t *server, char *args);

void right(drone_t *drone, server_t *server, char *args);

void left(drone_t *drone, server_t *server, char *args);

void look(drone_t *drone, server_t *server, char *args);

void inventory(drone_t *drone, server_t *server, char *args);

void broadcast(drone_t *drone, server_t *server, char *args);

typedef struct {
    char *name;
    void (*function)(drone_t *drone, server_t *server, char *arg);
    int duration;
} command_t;

static const command_t commands[] = {
    {"Forward", &forward},
    {"Right", &right},
    {"Left", &left},
    {"Look", &look},
    {"Inventory", &inventory},
    {"Broadcast", &broadcast},
    {NULL, NULL}
};
