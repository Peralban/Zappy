/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_len_before_char.c
*/

#include "lib/my.h"
#include <stdlib.h>

int my_len_before_char(char *str, char *delim)
{
    int i = 0;

    if (str == NULL || delim == NULL)
        return 0;
    while (str[i] != '\0' && !char_is_in_str(str[i], delim))
        i++;
    return i;
}
