/*
** EPITECH PROJECT, 2024
** check_return_value.c
** File description:
** DESCRIPTION
*/

#include <criterion/criterion.h>
#include "Server/server.h"

Test(return_error_str, fonction_fail)
{
    cr_assert_eq(check_return_value(-1, BIND), false);
}

Test(return_error_str, fonction_success)
{
    cr_assert_eq(check_return_value(0, BIND), true);
}
