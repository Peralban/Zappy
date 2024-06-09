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
void fork_player(client_t *client, server_t *server);
void connect_nbr(client_t *client, server_t *server);
void eject(client_t *client, server_t *server);
void incantation(client_t *client, server_t *server);

static const inventory_t incantation_level_prerequisites[7] = {
        {1, 1, 0, 0, 0, 0, 0},
        {2, 1, 1, 1, 0, 0, 0},
        {2, 2, 0, 1, 0, 2, 0},
        {4, 1, 1, 2, 0, 1, 0},
        {4, 1, 2, 1, 3, 0, 0},
        {6, 1, 2, 3, 0, 1, 0},
        {6, 2, 2, 2, 2, 2, 1},
};

bool check_incantation_condition(client_t *client, server_t *server);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server);
    bool (*condition)(client_t *client, server_t *server);
    int duration;
} command_t;

static const command_t commands_opt[] = {
    {"Forward", &forward, NULL, 7},
    {"Right", &right, NULL, 7},
    {"Left", &left, NULL, 7},
    {"Fork", &fork_player, NULL, 42},
    {"Connect_nbr", &connect_nbr, NULL, 7},
    {"Eject", &eject, NULL, 7},
    {"Incantation", &incantation, &check_incantation_condition, 300},
    {NULL, NULL, NULL, 0}
};
