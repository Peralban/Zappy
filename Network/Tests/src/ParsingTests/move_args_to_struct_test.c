/*
** EPITECH PROJECT, 2024
** move_args_to_server_struct.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Parsing/arguments_struct.h"
#include "lib/my.h"
#include "Parsing/parse_args.h"
#include <criterion/criterion.h>
#include <string.h>


Test(complete_integer_data, should_return_true_when_any_value_is_zero_or_negative)
{
    server_t server;
    char *args[] = {"-5465", "0", "10", "team1 team2", "10", "10", "10"};

    cr_assert_not(complete_integer_data(&server, args));
}

Test(complete_integer_data, should_return_false_when_all_values_are_positive)
{
    server_t server;
    char *args[] = {"5465", "1234", "7897", "10", "10", "10", "10"};

    cr_assert(complete_integer_data(&server, args));
}

Test(move_args_to_server_struct, should_return_null_when_team_names_parsing_fails)
{
    char **args = malloc(sizeof(char *) * 8);
    args[0] = "5465";
    args[1] = "1234";
    args[2] = "10";
    args[6] = "10";
    args[4] = "10";
    args[5] = "10";
    args[3] = NULL;

    cr_assert_null(move_args_to_server_struct(args));
}

Test(move_args_to_server_struct, should_return_null_when_any_value_is_zero_or_negative)
{
    char **args = malloc(sizeof(char *) * 8);
    args[0] = "-5465";
    args[1] = "0";
    args[2] = "10";
    args[6] = "10";
    args[4] = "10";
    args[5] = "10";
    args[3] = "team1 team2";

    //cr_assert_null(move_args_to_server_struct(args));
}

Test(move_args_to_server_struct, should_return_server_when_all_values_are_valid)
{
    char **args = malloc(sizeof(char *) * 8);
    args[0] = "5465";
    args[1] = "1234";
    args[2] = "10";
    args[6] = "10";
    args[4] = "10";
    args[5] = "10";
    args[3] = "team1 team2";

    cr_assert_not_null(move_args_to_server_struct(args));
}