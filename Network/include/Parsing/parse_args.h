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
 * This function takes the argument count and argument vector
 * (typically from main function)
 * and converts them into an array of strings for easier manipulation.
 *
 * @param ac The argument count.
 * @param av The argument vector.
 * @return Returns a pointer to the first element of the newly created
 * array of strings.
 */
char **get_array_from_args(int ac, char **av);

/**
 * @brief Moves the arguments from the array to the server structure.
 *
 * This function takes an array of strings (typically the one created by
 * get_array_from_args)
 * and a pointer to a server structure. It then moves the arguments from
 * the array to the
 * appropriate fields in the server structure.
 *
 * @param args The array of arguments.
 */
server_t *move_args_to_server_struct(char **args);

/**
 * @brief Prints an error message if the number of arguments is less than 13.
 *
 * This function checks if the argument count is less than 13. If it is, it
 * prints an error message.
 *
 * @param ac The argument count.
 * @return Returns true if the argument count is less than 13,
 * or false otherwise.
 */
bool print_param_error(int ac);

/**
 * @brief Checks all flags in the argument vector.
 *
 * This function iterates over all flags and checks
 * if the current argument matches any of the flags.
 * If a match is found, it calls the do_parsing_argument function.
 *
 * @param data A structure containing the argument vector, a flag
 * indicating if the current argument is a name,
 * the array of arguments, and a boolean array indicating which flags have been
 * found.
 * @param i A pointer to the current index in the argument vector.
 */
void check_all_flags(parsing_argument_t data, int *i);

/**
 * @brief Parses an argument.
 *
 * This function takes a flag and its corresponding value from the argument
 * vector and moves them to the array of arguments.
 * If the flag is 'NAMES', it appends the current argument to the array[NAMES]
 * instead of assigning the next argument.
 *
 * @param data A structure containing the argument vector, a flag indicating
 * if the current argument is a name,
 * the array of arguments, and a boolean array indicating which flags have
 * been found.
 * @param i A pointer to the current index in the argument vector.
 * @param j The index of the current flag in the FLAGS array.
 */
void do_parsing_argument(parsing_argument_t data, int *i, int j);

/**
 * @brief Returns the array of arguments or NULL if any flag is missing.
 *
 * This function checks if all flags have been found. If any flag is missing,
 * it prints an error message and returns NULL.
 * Otherwise, it returns the array of arguments.
 *
 * @param array The array of arguments.
 * @param args A boolean array indicating which flags have been found.
 * @return Returns the array of arguments if all flags have been found,
 * or NULL otherwise.
 */
char **return_array(char **array, const bool *args);

/**
 * @brief Converts the string arguments to integer and
 * assigns them to the server structure.
 *
 * This function takes a pointer to a server structure and an array
 * of string arguments. It converts the string arguments
 * to integers and assigns them to the appropriate fields in the server
 * structure. If any of the converted integers is less
 * than or equal to zero, it prints an error message and returns true.
 * Otherwise, it returns false.
 *
 * @param server A pointer to the server structure.
 * @param args The array of string arguments.
 * @return Returns true if any of the converted integers is less than
 * or equal to zero, or false otherwise.
 */
bool complete_integer_data(server_t *server, char **args);
