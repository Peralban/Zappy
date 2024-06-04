/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_len_before_char.c
*/

#include "lib/my.h"
#include <criterion/criterion.h>

Test(my_len_before_char, should_return_zero_when_str_or_delim_is_null)
{
    cr_assert_eq(my_len_before_char(NULL, "a"), 0);
    cr_assert_eq(my_len_before_char("abc", NULL), 0);
}

Test(my_len_before_char, should_return_zero_when_delim_is_first_char_in_str)
{
    cr_assert_eq(my_len_before_char("abc", "a"), 0);
}

Test(my_len_before_char, should_return_length_of_str_when_delim_is_not_in_str)
{
    cr_assert_eq(my_len_before_char("abc", "d"), 3);
}

Test(my_len_before_char, should_return_index_of_delim_in_str)
{
    cr_assert_eq(my_len_before_char("abc", "b"), 1);
}