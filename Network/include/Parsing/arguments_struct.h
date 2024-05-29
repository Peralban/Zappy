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

/**
 * @enum args_name
 * @brief Enumerates the different argument types that can be passed
 * to the program.
 */
enum args_name {
    PORT,
    WIDTH,
    HEIGHT,
    NAMES,
    CLIENTS_NB,
    FREQ,
    ALL_FLAGS
};

/**
 * @struct arg_processing_s
 * @brief Structure to hold the state of argument processing.
 */
typedef struct arg_processing_s {
    char **array;
    int *array_index;
    bool *n_flag;
    bool args[6];
} arg_processing_t;

/**
 * @struct parsing_argument_s
 * @brief Structure to hold the state of argument parsing.
 */
typedef struct parsing_argument_s {
    char *const *av;
    bool *n_flag;
    char **array;
    bool *args;
} parsing_argument_t;
