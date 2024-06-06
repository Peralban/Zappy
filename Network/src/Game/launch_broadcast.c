/*
** EPITECH PROJECT, 2024
** launch_broadcast.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Game/game.h"

static int *get_distance(drone_t *drone, drone_t *target)
{
    int *distance = malloc(sizeof(int) * 2);

    distance[0] = target->x - drone->x;
    distance[1] = target->y - drone->y;
    return distance;
}

bool launch_broadcast(drone_t *drone, server_t *server, char *args)
{
    int *distance;
    orientation_t ori = drone->orientation;
    if (args == NULL)
        return false;
    for (client_list_t *tmp = server->list; tmp; tmp = tmp->next) {
        if (tmp->client->drone->id == drone->id)
            continue;
        distance = get_distance(drone, tmp->client->drone);
        printf("message from %d %d to %d %d\n", drone->x, drone->y, tmp->client->drone->x, tmp->client->drone->y);
        printf("distance %d %d\n", distance[0], distance[1]);
    }
    return true;
}
