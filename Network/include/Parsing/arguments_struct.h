/*
** EPITECH PROJECT, 2024
** parse_args.h
** File description:
** DESCRIPTION
*/

#pragma once

#include <stdlib.h>

/**
 *  -p port port number
 *  -x width width of the world
 *  -y height height of the world
 *  -n name1 name2 ... name of the team
 *  -c clientsNb number of authorized clients per team
 *  -f freq reciprocal of time unit for execution of actions
 */

enum args_type {
    INT,
    STRING
};

enum args_name {
    PORT,
    WIDTH,
    HEIGHT,
    NAMES,
    CLIENTS_NB,
    FREQ,
    ALL_FLAGS
};

typedef struct arg_processing_s {
    char **array;
    int *array_index;
    bool *n_flag;
    bool args[6];
} arg_processing_t;

typedef struct parsing_argument_s {
    char *const *av;
    bool *n_flag;
    char **array;
    bool *args;
} parsing_argument_t;
