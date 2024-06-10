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
    return_str[strlen(return_str) - 1] = '\0';
    return return_str;
}

static char *look_at(drone_t *drone, server_t *server, int nb_observable,
    int level)
{
    orientation_t or = drone->orientation;
    int mo[] = {-level, level, -level, level};
    int re[] = {drone->x, drone->y};
    int ne[] = {0, 0};
    int ma[] = {server->info_game.width, server->info_game.height};
    char *return_str = calloc(1, sizeof(char) * 2048);
    axes_t lk[4][2] = {{X, Y}, {Y, X}, {X, Y}, {Y, X}};
    char *tmp;

    ne[lk[or][0]] = (re[lk[or][0]] + mo[or] + ma[lk[or][0]]) % ma[lk[or][0]];
    for (int j = 0; j < nb_observable; j++) {
        ne[lk[or][1]] =
        (re[lk[or][1]] + j + ma[lk[or][1]]) % ma[lk[or][1]];
        tmp = scan_tile(&(server->game->map[ne[X]][ne[Y]]));
        strcat(return_str, tmp);
        if (j != 0)
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
    for (int i = 0; i < drone->level + 1; i++) {
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
