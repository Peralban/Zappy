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

bool do_parsing_argument(parsing_argument_t data, int *i, int j)
{
    char *tmp = strdup(data.av[*i]);

    if (*data.n_flag) {
        strcat(data.array[NAMES], " ");
        if (strcmp(tmp, "graphic") == 0) {
            free(tmp);
            printf("Invalid team name, can't be 'graphic'\n");
            return true;
        }
        strcat(data.array[NAMES], tmp);
    } else {
        data.args[j] = true;
        data.array[j] = data.av[*i + 1];
        (*i)++;
        *data.n_flag = (j == NAMES);
    }
    free(tmp);
    return false;
}

bool check_all_flags(parsing_argument_t data, int *i)
{
    for (int j = 0; j < ALL_FLAGS; j++) {
        if (strcmp(data.av[*i], FLAGS[j]) == 0 || *data.n_flag) {
            return do_parsing_argument(data, i, j);
        }
    }
    printf("Invalid flag \'%s\'\n", data.av[*i]);
    return true;
}

bool print_param_error(int ac)
{
    if (ac < 13) {
        printf("Not enough arguments\n");
        return true;
    }
    return false;
}

static void *free_and_return(void *object)
{
    free(object);
    return NULL;
}

char **get_array_from_args(int ac, char **av)
{
    bool n_flag = false;
    char **array = malloc(sizeof(char *) * (ALL_FLAGS + 1));
    bool args[ALL_FLAGS] = {0};
    char **args_array;
    parsing_argument_t data = {av, &n_flag, array, args};

    print_param_error(ac);
    if (data.array == NULL)
        return NULL;
    for (int i = 1; i < ac; i++) {
        if (data.av[i][0] == '-')
            *data.n_flag = false;
        if (check_all_flags(data, &i))
            return free_and_return(array);
    }
    args_array = return_array(data.array, data.args);
    if (args_array == NULL || ac < 13)
        return free_and_return(array);
    return args_array;
}
