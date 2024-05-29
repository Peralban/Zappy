/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** number_char.c
*/

#include <stdlib.h>

int get_nbr_of_char(char *str, char c)
{
    int nb = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            nb++;
    return nb;
}
