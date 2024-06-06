/*
** EPITECH PROJECT, 2022
** epitech
** File description:
** my_str_to_word_array.c
*/

#include "lib/my.h"
#include <criterion/criterion.h>

Test(my_str_to_word_array, should_return_array_with_one_word)
{
    char **result = my_str_to_word_array("Hello", " ");
    cr_assert_str_eq(result[0], "Hello");
}
Test(my_str_to_word_array, should_return_null_when_str_or_delim_is_null)
{
    cr_assert_null(my_str_to_word_array(NULL, " "));
    cr_assert_null(my_str_to_word_array("Hello World", NULL));
}

Test(my_str_to_word_array, should_return_correct_word_array)
{
    char **result = my_str_to_word_array("Hello World", " ");
    cr_assert_str_eq(result[0], "Hello");
    cr_assert_str_eq(result[1], "World");
    my_free_array(result);
}

Test(my_free_array, should_free_array_without_errors)
{
    char **result = my_str_to_word_array("Hello World", " ");
    bool comp = strcmp(result[0], "Hello") == 0 && strcmp(result[1], "World") == 0;
    cr_assert(comp);
    my_free_array(result);
    bool comp2 = strcmp(result[0], "Hello") == 0 && strcmp(result[1], "World") == 0;
    cr_assert_not(comp2);
}