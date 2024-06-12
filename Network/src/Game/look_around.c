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
    char *return_str = calloc(1024, sizeof(char));
    char *type_str[] = {"food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras", "thystame"};

    for (int i = 0; i < 7; i++) {
        for (int k = 0; k < tile->inventory[i]; k++) {
            strcat(return_str, type_str[i]);
            strcat(return_str, " ");
        }
    }
    for (linked_list_drone_t *tmp = tile->drone_list;
    tmp != NULL; tmp = tmp->next) {
        strcat(return_str, "player");
        strcat(return_str, " ");
    }
    if (strlen(return_str) > 0)
        return_str[strlen(return_str) - 1] = '\0';
    return return_str;
}

static int for_s(orientation_t orientation, int value)
{
    if (orientation == 0 || orientation == 3)
        return 0;
    return value - 1;
}

static bool for_c(orientation_t orientation, int i, int value)
{
    if (orientation == 0 || orientation == 3)
        return (i < value);
    return i >= 0;
}

static void for_i(orientation_t orientation, int *i)
{
    if (orientation == 0 || orientation == 3) {
        (*i)++;
    } else
        (*i)--;
}

static char *look_at(drone_t *drone, server_t *server, int nb_observable,
    int level)
{
    orientation_t ori = drone->orientation;
    int mov[] = {-level, -level, level, level};
    int ref[2][2] = {{drone->x, drone->y}, {0, 0}};
    int max[] = {server->info_game.width, server->info_game.height};
    char *return_str = calloc(1024, sizeof(char));
    axes_t link[4][2] = {{Y, X}, {X, Y}, {Y, X}, {X, Y}};
    char *tmp;

    ref[1][link[ori][0]] =
    (ref[0][link[ori][0]] + mov[ori] + max[link[ori][0]]) % max[link[ori][0]];
    for (int j = for_s(ori, nb_observable); for_c(ori, j, nb_observable);) {
        ref[1][link[ori][1]] =
        (ref[0][link[ori][1]] + (j - nb_observable / 2) + max[link[ori][1]]) %
        max[link[ori][1]];
        tmp = scan_tile(&(server->game->map[ref[1][X]][ref[1][Y]]));
        strcat(return_str, strcat(tmp, ", "));
        free(tmp);
        for_i(ori, &j);
    }
    return return_str;
}

char *look_around(drone_t *drone, server_t *server)
{
    int nb_observable;
    char *return_str = calloc(1024, sizeof(char));
    char *tmp2;

    if (return_str == NULL)
        return NULL;
    strcat(return_str, "[");
    for (int i = 0; i < drone->level + 1; i++) {
        nb_observable = (i * 2) + 1;
        tmp2 = look_at(drone, server, nb_observable, i);
        strcat(return_str, tmp2);
        free(tmp2);
    }
    return_str[strlen(return_str) - 2] = '\0';
    strcat(return_str, "]\n");
    return return_str;
}
