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
    bool return_null = false;
    char **array = malloc(sizeof(char *) * ALL_FLAGS + 1);
    bool args[ALL_FLAGS] = {false, false, false, false, false, false};

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
                    args[j] = true;
                    array[j] = av[i + 1];
                    i++;
                    n_flag = (j == NAMES);
                }
                break;
            }
        }
    }
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