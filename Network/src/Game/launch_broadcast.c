/*
** EPITECH PROJECT, 2024
** launch_broadcast.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Game/game.h"
#include <math.h>

static int *get_distance(drone_t *drone, drone_t *target, info_game_t *info_game)
{
    int *return_distance = malloc(sizeof(int) * 2);
    int tmp_dist[4][2] = {
        {target->x - drone->x, target->y - drone->y - info_game->height},
        {target->x - drone->x, target->y - drone->y + info_game->height},
        {target->x - drone->x - info_game->width, target->y - drone->y},
        {target->x - drone->x + info_game->width, target->y - drone->y}
    };

    if (return_distance == NULL)
        return NULL;
    return_distance[0] = target->x - drone->x;
    return_distance[1] = target->y - drone->y;
    for (int i = 0; i < 4; i++) {
        if (sqrt(pow(tmp_dist[i][0], 2) + pow(tmp_dist[i][1], 2)) <
        sqrt(pow(return_distance[0], 2) + pow(return_distance[1], 2))) {
            return_distance[0] = tmp_dist[i][0];
            return_distance[1] = tmp_dist[i][1];
        }
    }
    return return_distance;
}

static int get_square(int angle, orientation_t ori)
{
    bool conditions[10] = {
        angle < 0 && angle > -45, angle == -45, angle > -135 && angle < -45,
        angle == -135, angle >= -180 && angle < -135, angle >= 0 && angle < 45,
        angle == 45, angle > 45 && angle < 135, angle == 135,
        angle >= 135 && angle <= 180
    };
    int values[4][10] = {
        {7, 8, 1, 2, 3, 7, 6, 5, 4, 3}, // NORTH
        {1, 2, 3, 4, 5, 1, 8, 7, 6, 5}, // EAST
        {3, 4, 5, 6, 7, 3, 2, 1, 8, 7}, // SOUTH
        {5, 6, 7, 8, 1, 5, 4, 3, 2, 1}  // WEST
    };

    for (int i = 0; i < 10; i++)
        if (conditions[i])
            return values[ori][i];
    return 0;
}

static char *form_message(char *args, int first_square)
{
    char *message = malloc(sizeof(char) * (strlen(args) + strlen("message , ") + 2));

    sprintf(message, "message %d, %s\n", first_square, args);
    return message;
}

bool launch_broadcast(drone_t *drone, server_t *server, char *args)
{
    int *distance;
    int angle_from_launcher;
    orientation_t ori = drone->orientation;
    int first_square = 0;
    char *message;

    if (args == NULL)
        return false;
    for (client_list_t *tmp = server->list; tmp; tmp = tmp->next) {
        if (tmp->client->drone->id == drone->id)
            continue;
        distance = get_distance(drone, tmp->client->drone, &server->info_game);
        angle_from_launcher = atan2(distance[1], distance[0]) * 180 / M_PI;
        first_square = get_square(angle_from_launcher, ori);
        message = form_message(args, first_square);
        send(tmp->client->socket, message, strlen(message), 0);
        free(distance);
        free(message);
    }
    return true;
}
