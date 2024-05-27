/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** return_error_str.c
*/

#include <stdlib.h>
#include <string.h>

static const char *str_fusion(const char *str1, char *str2)
{
    char *result = NULL;

    if (str2 == NULL) {
        result = malloc(strlen(str1) + 3);
        if (result == NULL)
            return (str1);
        strcpy(result, str1);
        strcat(result, "\r\n");
        return (result);
    }
    result = malloc(strlen(str1) + strlen(str2) + 3);
    if (result == NULL)
        return (str1);
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, "\r\n");
    return (result);
}

const char *return_error(char *error, char *complement)
{
    return (str_fusion(error, complement));
}
