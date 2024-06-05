/*
** EPITECH PROJECT, 2024
** look_around.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

static char *look_at(drone_t *drone, server_t *server, int nb_observable, int level)
{
    orientation_t ori = drone->orientation;
    int movement[] = {-level, level, -level, level};
    int ref_coord[] = {drone->x, drone->y};
    int new_coord[] = {0, 0};
    int max[] = {server->info_game.width, server->info_game.height};
    //char *return_str;

    if (ori == NORTH || ori == SOUTH)
        new_coord[X] = (ref_coord[X] + movement[ori] + max[X]) % max[X];
    else
        new_coord[Y] = (ref_coord[Y] + movement[ori] + max[Y]) % max[Y];
    for (int j = 0; j < nb_observable; j++) {
        if (ori == NORTH || ori == SOUTH)
            new_coord[Y] = (ref_coord[Y] + max[Y] - j) % max[Y];
        else
            new_coord[X] = (ref_coord[X] + max[X] - j) % max[X];
        printf("New coord: %d %d\n", new_coord[X], new_coord[Y]);
        //strcat(return_str, scan_tile(server->game->map[new_coord[X]][new_coord[Y]]));
    }
    return NULL;
}

void look_around(drone_t *drone, server_t *server)
{
    int nb_observable;
    //char *return_str = calloc(1, sizeof(char));

    printf("Look around\n");
    //if (return_str == NULL)
    //    return;
    //strcat(return_str, "[");
    for (int i = 0; i < drone->level; i++) {
        nb_observable = (i * 2) + 1;
        look_at(drone, server, nb_observable, i);
        //printf(",");
    }
    //printf("]\n");
}
