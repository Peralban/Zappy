/*
** EPITECH PROJECT, 2024
** InGameTests.c
** File description:
** DESCRIPTION
*/

#include <criterion/criterion.h>
#include "Server/server.h"

Test(init_game, basic_test)
{
    info_game_t info_game = {10, 10, 2, (char *[]){"team1", "team2"}, 10, 10};
    in_game_t *game = init_game(info_game);

    cr_assert_not_null(game);
}