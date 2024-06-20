/*
** EPITECH PROJECT, 2024
** launch_broadcast.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Game/game.h"
#include <math.h>

static int *get_distance(drone_t *drone, drone_t *target, info_game_t info)
{
    int *return_distance = malloc(sizeof(int) * 2);
    int tmp_dist[4][2] = {
        {target->x - drone->x, target->y - drone->y - info.height},
        {target->x - drone->x, target->y - drone->y + info.height},
        {target->x - drone->x - info.width, target->y - drone->y},
        {target->x - drone->x + info.width, target->y - drone->y}
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
        {7, 8, 1, 2, 3, 7, 6, 5, 4, 3},
        {1, 2, 3, 4, 5, 1, 8, 7, 6, 5},
        {3, 4, 5, 6, 7, 3, 2, 1, 8, 7},
        {5, 6, 7, 8, 1, 5, 4, 3, 2, 1}
    };

    for (int i = 0; i < 10; i++)
        if (conditions[i])
            return values[ori][i];
    return 0;
}

static char *form_message(char *args, int first_square)
{
    char *message = malloc(sizeof(char) * (strlen(args) +
    strlen("message , ") + 64));

    sprintf(message, "message %d, %s\n", first_square, args);
    return message;
}

static void send_broadcast(drone_t *drone, const server_t *server,
    char *args, client_t *tmp)
{
    int *distance = get_distance(drone, tmp->drone, server->info_game);
    int angle_from_launcher =
        (int)(atan2(distance[1], distance[0]) * 180 / M_PI);
    int first_square = get_square(angle_from_launcher, drone->orientation);
    char *message;

    if (distance[0] == 0 && distance[1] == 0)
        message = form_message(args, 0);
    else
        message = form_message(args, first_square);
    send(tmp->socket, message, strlen(message), 0);
    free(distance);
    free(message);
}

bool launch_broadcast(drone_t *drone, server_t *server, char *args)
{
    if (args == NULL)
        return false;
    for (client_list_t *tmp = server->list; tmp; tmp = tmp->next) {
        if (tmp->client->drone == NULL || tmp->client->drone->id == drone->id)
            continue;
        send_broadcast(drone, server, args, tmp->client);
    }
    return true;
}
