/*
** EPITECH PROJECT, 2024
** init_in_game_stuct.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include <unistd.h>
#include "Parsing/parse_args.h"
#include "Server/game.h"
#include "lib/my.h"

static tile_t **get_tile(int x, int y)
{
    tile_t **tile = malloc(sizeof(tile_t) * (x + 1));

    if (tile == NULL)
        return NULL;
    for (int i = 0; i < x; i++) {
        tile[i] = malloc(sizeof(tile_t) * (y + 1));
        if (tile[i] == NULL)
            return NULL;
    }
    return tile;
}

static team_t *get_team(char **team_names)
{
    int nb_teams = my_array_len(team_names);
    team_t *teams = malloc(sizeof(team_t) * (nb_teams + 1));

    if (teams == NULL)
        return NULL;
    for (int i = 0; i < nb_teams; i++) {
        teams[i].name = team_names[i];
        teams[i].connected_clients = 0;
        teams[i].drone = NULL;
    }
    return teams;
}

in_game_t *init_game(info_game_t info_game)
{
    in_game_t *game = malloc(sizeof(in_game_t));
    int nb_teams = my_array_len(info_game.team_names);

    if (game == NULL || nb_teams == 0)
        return NULL;
    game->map = get_tile(info_game.width, info_game.height);
    if (game->map == NULL)
        return NULL;
    game->teams = get_team(info_game.team_names);
    if (game->teams == NULL)
        return NULL;
    return game;
}
