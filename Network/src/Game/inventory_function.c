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
    char *str = calloc(1, sizeof(char) * 128);

    sprintf(str, "%d", nb);
    return str;
}

static int count_item(drone_t *drone)
{
    int nbr_item = 0;

    for (int i = 0; i < 7; i++)
        if (drone->inventory[i] != 0)
            nbr_item++;
    return nbr_item;
}

static char *finish_str(char *return_str)
{
    strcat(return_str, "]\n");
    return return_str;
}

char *display_inventory(drone_t *drone)
{
    char *return_str = calloc(1024, sizeof(char));
    char *type_str[] = {"food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras", "thystame"};
    int nbr_item = count_item(drone);
    char *tmp;

    strcat(return_str, "[");
    for (int i = 0; i < 7; i++) {
        if (drone->inventory[i] != 0) {
            strcat(return_str, type_str[i]);
            strcat(return_str, " ");
            tmp = my_itoa(drone->inventory[i]);
            strcat(return_str, tmp);
            free(tmp);
            nbr_item--;
        }
        if (nbr_item > 0 && drone->inventory[i] != 0)
            strcat(return_str, ", ");
    }
    return finish_str(return_str);
}
