/*
** EPITECH PROJECT, 2024
** parse_args.h
** File description:
** DESCRIPTION
*/

#pragma once

#include <stdlib.h>
#include "Server/server.h"
#include "Parsing/arguments_struct.h"

/**
 *  -p port port number
 *  -x width width of the world
 *  -y height height of the world
 *  -n name1 name2 ... name of the team
 *  -c clientsNb number of authorized clients per team
 *  -f freq reciprocal of time unit for execution of actions
 */

/**
 * @brief Converts the argument vector into an array of strings.
 *
 * This function takes the argument count and argument vector (typically from main function)
 * and converts them into an array of strings for easier manipulation.
 *
 * @param ac The argument count.
 * @param av The argument vector.
 * @return Returns a pointer to the first element of the newly created array of strings.
 */
char **get_array_from_args(int ac, char **av);

/**
 * @brief Moves the arguments from the array to the server structure.
 *
 * This function takes an array of strings (typically the one created by get_array_from_args)
 * and a pointer to a server structure. It then moves the arguments from the array to the
 * appropriate fields in the server structure.
 *
 * @param args The array of arguments.
 * @param server The server structure.
 */
void move_args_to_struct(args_t **args, server_t *server);


