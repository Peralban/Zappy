/*
** EPITECH PROJECT, 2022
** lib
** File description:
** my.h
*/

#pragma once

#include <stdbool.h>

/**
 * @brief Check if a char is in a string
 * @param c The char to check.
 * @param str The string to check.
 * @return true if the char is in the string, false otherwise.
*/

bool char_is_in_str(char c, char *str);

/**
 * @brief Return the number of char in a string.
 * @param str The string to check.
 * @param c The char to check.
 * @return The number of char in the string.
*/

int get_nbr_of_char(char *str, char c);

/**
 * @brief Return the lenght of a string before a char.
 * @param str The string to check.
 * @param delim The char of reference.
 * @return The lenght of the string before the char.
 * @warning The string must be terminated by '\0'.
*/

int my_len_before_char(char *str, char *delim);

/**
 * @brief Return an array of string from a string.
 * @param str The string to split.
 * @param delim A string of delimiter.
 * @return An array of string. If the string is NULL, return NULL.
 * @warning The string must be terminated by '\0'.
*/

char **my_str_to_word_array(char *str, char *delim);


/**
 * @brief This function will be print an array of string.
 * @param array The array of string to print.
 * @return Nothing.
*/
void my_free_array(char **array);

/**
 * @brief Counts the number of elements in a null-terminated array of strings.
 * @param array The null-terminated array of strings.
 * @return The number of elements in the array.
 */
int my_array_len(char **array);

/**
 * @brief Counts the number of words in a string.
 *
 * This function takes a string and a delimiter as input and
 * returns the number of words in the string.
 * A word is defined as a sequence of characters separated
 * by one or more of the characters in the delimiter string.
 *
 * @param str The string to be split into words.
 * @param delim A string containing the delimiter characters.
 * @return The number of words in the string.
 */
int word_nbr(char *str, char *delim);
