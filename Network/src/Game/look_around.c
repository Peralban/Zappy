/*
** EPITECH PROJECT, 2024
** look_around.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

static char *scan_tile(tile_t *tile)
{
    char *return_str = calloc(1, sizeof(char) * 1024);
    char *type_str[] = {"food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras", "thystame"};

    for (int i = 0; i < 7; i++) {
        for (int y = 0; y < tile->inventory[i]; y++) {
            strcat(return_str, type_str[i]);
            strcat(return_str, " ");
        }
    }
    return_str[strlen(return_str) - 1] = '\0';
    for (linked_list_drone_t *tmp = tile->drone_list;
    tmp != NULL; tmp = tmp->next) {
        strcat(return_str, "player");
        if (tmp->next != NULL)
            strcat(return_str, " ");
    }
    return return_str;
}

static char *look_at(drone_t *drone, server_t *server, int nb_observable,
    int level)
{
    orientation_t ori = drone->orientation;
    int mov[] = {-level, level, -level, level};
    int ref[] = {drone->x, drone->y};
    int new[] = {0, 0};
    int max[] = {server->info_game.width, server->info_game.height};
    char *return_str = calloc(1, sizeof(char) * 1024);
    axes_t link[4][2] = {{X, Y}, {Y, X}, {X, Y}, {Y, X}};
    char *tmp;

    new[link[ori][0]] =
    (ref[link[ori][0]] + mov[ori] + max[link[ori][0]]) % max[link[ori][0]];
    for (int j = 0; j < nb_observable; j++) {
        new[link[ori][1]] =
        (ref[link[ori][1]] + j + max[link[ori][1]]) % max[link[ori][1]];
        tmp = scan_tile(&(server->game->map[new[X]][new[Y]]));
        strcat(return_str, tmp);
        strcat(return_str, ",");
        free(tmp);
    }
    return return_str;
}

char *look_around(drone_t *drone, server_t *server)
{
    int nb_observable;
    char *return_str = calloc(1, sizeof(char) * 4096);
    char *tmp;

    if (return_str == NULL)
        return NULL;
    strcat(return_str, "[");
    for (int i = 0; i < drone->level; i++) {
        nb_observable = (i * 2) + 1;
        tmp = look_at(drone, server, nb_observable, i);
        strcat(return_str, tmp);
        free(tmp);
        if (i != drone->level - 1)
            strcat(return_str, ",");
    }
    strcat(return_str, "]\n");
    return return_str;
}
