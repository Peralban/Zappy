/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_str_to_word_array.c
*/

#include "lib/my.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int word_nbr(char *str, char *delim)
{
    int nbr_word = 0;
    bool is_word = false;

    if (str == NULL || delim == NULL)
        return 0;
    for (int index = 0; str[index] != '\0'; index++) {
        if (char_is_in_str(str[index], delim) == false && is_word == false) {
            nbr_word += 1;
            is_word = true;
        }
        if (char_is_in_str(str[index], delim) == true) {
            is_word = false;
        }
    }
    return nbr_word;
}

static char **end_of_str(char ***array, int string)
{
    (*array)[string] = NULL;
    return *array;
}

static char **get_string(char *str, char *delim, char ***array)
{
    int size_str;
    int string = 0;

    for (int index = 0; str[index] != '\0'; index++) {
        if (!char_is_in_str(str[index], delim)) {
            size_str = my_len_before_char(str + index, delim);
            (*array)[string] = malloc(sizeof(char) * size_str + 1);
            strncpy((*array)[string], str + index, size_str);
            (*array)[string][size_str] = '\0';
            index += size_str;
            string += 1;
        }
        if (str[index] == '\0')
            break;
    }
    return end_of_str(array, string);
}

char **my_str_to_word_array(char *str, char *delim)
{
    int nbr_word = word_nbr(str, delim);
    char **array = malloc(sizeof(char *) * (nbr_word + 1));

    if (str == NULL || delim == NULL)
        return NULL;
    if (nbr_word == 1) {
        array[0] = strdup(str);
        array[1] = NULL;
        return array;
    } else
        return get_string(str, delim, &array);
}

void my_free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

int my_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}
