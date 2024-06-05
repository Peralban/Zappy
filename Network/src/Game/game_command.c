/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "Game/game.h"
#include "Game/game_command.h"
#include "Game/game_functions.h"

void forward(drone_t *drone, server_t *server)
{
    move(drone, server);
}

void right(drone_t *drone, server_t *server)
{
    (void)server;
    turn(drone, RIGHT);
}

void left(drone_t *drone, server_t *server)
{
    (void)server;
    turn(drone, LEFT);
}
