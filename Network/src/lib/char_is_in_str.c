/*
** EPITECH PROJECT, 2022
** lib
** File description:
** char_is_in_str.c
*/

#include <stdbool.h>
#include <stdlib.h>

bool char_is_in_str(char c, char *str)
{
    if (str == NULL)
        return false;
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            return true;
    return false;
}
