/*
** EPITECH PROJECT, 2024
** InGameTests.c
** File description:
** DESCRIPTION
*/

#include <criterion/criterion.h>
#include "Server/server.h"

Test(init_game, init_game_should_return_null_when_nb_teams_is_zero)
{
    info_game_t info_game = {10, 10, (char *[]){"team1", "team2"}, 10, 10};
    in_game_t *game = init_game(info_game);

    cr_assert_not_null(game);
}