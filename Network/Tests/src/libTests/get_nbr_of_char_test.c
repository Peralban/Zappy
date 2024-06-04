/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** number_char.c
*/

#include "lib/my.h"
#include <criterion/criterion.h>

Test(get_nbr_of_char, function_true)
{
    cr_assert_eq(get_nbr_of_char("abc", 'a'), 1);
}

Test(get_nbr_of_char, function_false)
{
    cr_assert_eq(get_nbr_of_char("abc", 'd'), 0);
}

Test(get_nbr_of_char, function_null)
{
    cr_assert_eq(get_nbr_of_char(NULL, 'd'), 0);
}