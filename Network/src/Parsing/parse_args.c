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

char **get_array_from_args(int ac, char **av)
{
    bool n_flag = false;
    char **array = malloc(sizeof(char *) * ALL_FLAGS + 1);

    if (array == NULL)
        return NULL;
    array[NAMES] = malloc(sizeof(char) * 1);
    if (array[NAMES] == NULL)
        return NULL;
    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-')
            n_flag = false;
        for (int j = 0; j < ALL_FLAGS; j++) {
            if (strcmp(av[i], FLAGS[j]) == 0 || n_flag) {
                if (n_flag) {
                    array[NAMES] = strcat(array[NAMES], " ");
                    array[NAMES] = strcat(array[NAMES], av[i]);
                } else {
                    array[j] = av[i + 1];
                    i++;
                    n_flag = (j == NAMES);
                }
                break;
            }
        }
    }
    array[ALL_FLAGS] = NULL;
    return array;
}
