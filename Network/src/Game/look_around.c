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
    for (linked_list_drone_t *tmp = tile->drone_list;
    tmp != NULL; tmp = tmp->next) {
        strcat(return_str, "player");
        strcat(return_str, " ");
    }
    return return_str;
}

static void look_at_bis(char **return_str, char *tmp, int j)
{
    strcat(*return_str, tmp);
    if (j != 0)
        strcat(*return_str, ",");
}

static char *look_at(drone_t *drone, server_t *server, int nb_observable,
    int level)
{
    orientation_t ori = drone->orientation;
    int mov[] = {-level, level, -level, level};
    int ref[2][2] = {{drone->x, drone->y}, {0, 0}};
    int max[] = {server->info_game.width, server->info_game.height};
    char *return_str = calloc(1, sizeof(char) * 1024);
    axes_t link[4][2] = {{X, Y}, {Y, X}, {X, Y}, {Y, X}};
    char *tmp;

    ref[1][link[ori][0]] =
    (ref[0][link[ori][0]] + mov[ori] + max[link[ori][0]]) % max[link[ori][0]];
    for (int j = 0; j < nb_observable; j++) {
        ref[1][link[ori][1]] =
        (ref[0][link[ori][1]] + j + max[link[ori][1]]) % max[link[ori][1]];
        tmp = scan_tile(&(server->game->map[ref[1][X]][ref[1][Y]]));
        look_at_bis(&return_str, tmp, j);
        free(tmp);
    }
    return return_str;
}

char *look_around(drone_t *drone, server_t *server)
{
    int nb_observable;
    char *return_str = calloc(1, sizeof(char) * 1024);
    char *tmp[] = {"[", "]\n", ","};
    char *tmp2;

    if (return_str == NULL)
        return NULL;
    strcat(return_str, "[");
    for (int i = 0; i < drone->level + 1; i++) {
        nb_observable = (i * 2) + 1;
        tmp2 = look_at(drone, server, nb_observable, i);
        strcat(return_str, tmp2);
        free(tmp2);
        if (i != drone->level - 1)
            strcat(return_str, ",");
    }
    strcat(return_str, tmp[1]);
    return return_str;
}
