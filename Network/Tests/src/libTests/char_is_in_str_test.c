/*
** EPITECH PROJECT, 2022
** lib
** File description:
** char_is_in_str.c
*/

#include "lib/my.h"
#include <criterion/criterion.h>

Test(char_is_in_str, function_false)
{
    cr_assert_not(char_is_in_str('d', "abc"));
}

Test(char_is_in_str, function_true)
{
    cr_assert(char_is_in_str('a', "abc"));
}

Test(char_is_in_str, function_null)
{
    cr_assert_not(char_is_in_str('d', NULL));
}