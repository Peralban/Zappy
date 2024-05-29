/*
** EPITECH PROJECT, 2024
** parse_args.c
** File description:
** DESCRIPTION
*/

#include <criterion/criterion.h>
#include "Parsing/arguments_struct.h"
#include "Parsing/parse_args.h"

Test(return_array, should_return_null_when_args_are_false)
{
    bool args[ALL_FLAGS] = {0};
    char *array[ALL_FLAGS + 1] = {0};

    cr_assert_null(return_array(array, args));
}

Test(return_array, should_return_array_when_args_are_true)
{
    bool args[ALL_FLAGS] = {1, 1, 1, 1, 1, 1};
    char *array[ALL_FLAGS + 1] = {0};

    cr_assert_eq(return_array(array, args), array);
}

Test(print_param_error, should_print_error_when_ac_less_than_13)
{
    cr_assert_eq(print_param_error(12), true);
}

Test(get_array_from_args, should_return_null_when_ac_less_than_13)
{
    int ac = 12;
    char *av[] = {"program", "-p", "value", "-x", "value", "-y", "value", "-n", "value", "-c", "value", "-f", "value"};

    cr_assert_null(get_array_from_args(ac, av));
}

Test(get_array_from_args, should_return_array_when_ac_greater_than_12)
{
    int ac = 13;
    char *av[] = {"program", "-p", "value", "-x", "value", "-y", "value", "-n", "value", "-c", "value", "-f", "value", "extra"};

    cr_assert_not_null(get_array_from_args(ac, av));
}

Test(get_array_from_args, should_return_null_when_insufficient_arguments)
{
    char *av[] = {"program", "-p", "8080"};
    int ac = 3;

    cr_assert_null(get_array_from_args(ac, av));
}

Test(get_array_from_args, should_handle_flags_correctly)
{
    char *av[] = {"program", "-p", "8080", "-x", "10", "-y", "10", "-n", "name", "-c", "1", "-f", "100"};
    int ac = sizeof(av) / sizeof(char *);
    char **result = get_array_from_args(ac, av);

    cr_assert_not_null(result);
    cr_assert_str_eq(result[PORT], "8080");
    cr_assert_str_eq(result[WIDTH], "10");
    cr_assert_str_eq(result[HEIGHT], "10");
    cr_assert_str_eq(result[NAMES], "name");
    cr_assert_str_eq(result[CLIENTS_NB], "1");
    cr_assert_str_eq(result[FREQ], "100");
}