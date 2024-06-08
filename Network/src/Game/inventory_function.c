/*
** EPITECH PROJECT, 2024
** look_around.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

static char *my_itoa(int nb)
{
    char *str = calloc(1, sizeof(char) * 100);

    sprintf(str, "%d", nb);
    return str;
}

static int count_item(drone_t *drone)
{
    int nbr_item = 0;

    for (int i = 0; i < 7; i++)
        if (drone->inventory[i] != 0)
            nbr_item ++;
    return nbr_item;
}

static char *finish_str(drone_t *drone, char *return_str)
{
    char *tmp;

    if (drone->inventory[FOOD] != 0) {
        strcat(return_str, ", food ");
        tmp = my_itoa(drone->inventory[0]);
        strcat(return_str, tmp);
        free(tmp);
    }
    strcat(return_str, "]\n");
    return return_str;
}

char *display_inventory(drone_t *drone)
{
    char *return_str = calloc(1, sizeof(char) * 100);
    char *type_str[] = {"food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras", "thystame"};
    int nbr_item = count_item(drone);
    char *tmp;

    strcat(return_str, "[");
    for (int i = 1; i < 7; i++) {
        if (drone->inventory[i] != 0) {
            strcat(return_str, type_str[i - 1]);
            strcat(return_str, " ");
            tmp = my_itoa(drone->inventory[i]);
            strcat(return_str, tmp);
            free(tmp);
            nbr_item --;
        }
        if (nbr_item > 1 && drone->inventory[i] != 0)
            strcat(return_str, ", ");
    }
    return finish_str(drone, return_str);
}
