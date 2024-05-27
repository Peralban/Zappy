/*
** EPITECH PROJECT, 2024
** parse_args.c
** File description:
** DESCRIPTION
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Parsing/arguments_struct.h"
#include "Parsing/args_flag.h"

char **return_array(char **array, const bool *args)
{
    bool return_null = false;

    for (int i = 0; i < ALL_FLAGS; i++) {
        if (!args[i]) {
            printf("Missing argument %s\n", FLAGS[i]);
            return_null = true;
        }
    }
    if (return_null)
        return NULL;
    array[ALL_FLAGS] = NULL;
    return array;
}

void do_foo(foo_t data, int *i, int j) {
    if (*data.n_flag) {
        strcat(data.array[NAMES], " ");
        strcat(data.array[NAMES], strdup(data.av[*i]));
    } else {
        data.args[j] = true;
        data.array[j] = data.av[*i + 1];
        (*i)++;
        *data.n_flag = (j == NAMES);
    }
}

void check_all_flags(foo_t data, int *i)
{
    for (int j = 0; j < ALL_FLAGS; j++) {
        if (strcmp(data.av[*i], FLAGS[j]) == 0 || *data.n_flag) {
            do_foo(data, i, j);
            break;
        }
    }
}

char **get_array_from_args(int ac, char **av)
{
    bool n_flag = false;
    char **array = malloc(sizeof(char *) * (ALL_FLAGS + 1));
    bool args[ALL_FLAGS] = {0};
    foo_t data = {av, &n_flag, array, args};

    if (data.array == NULL)
        return NULL;
    data.array[NAMES] = malloc(sizeof(char) * 256);
    if (data.array[NAMES] == NULL)
        return NULL;
    for (int i = 1; i < ac; i++) {
        if (data.av[i][0] == '-')
            *data.n_flag = false;
        check_all_flags(data, &i);
    }
    return return_array(data.array, data.args);
}
