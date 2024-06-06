/*
** EPITECH PROJECT, 2024
** init_in_game_stuct.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Game/game.h"
#include "lib/my.h"

static tile_t **get_tile(int x, int y)
{
    tile_t **tile = malloc(sizeof(tile_t) * (x + 1));

    if (tile == NULL)
        return NULL;
    for (int i = 0; i < x; i++) {
        tile[i] = calloc((y), sizeof(tile_t));
        if (tile[i] == NULL)
            return NULL;
    }
    tile[x] = NULL;
    return tile;
}

static linked_list_egg_t *get_all_eggs(info_game_t info_game,
    linked_list_egg_t *egg_list)
{
    linked_list_egg_t *tmp;

    for (int i = 1; i < info_game.nb_client * info_game.nb_teams; i++) {
        tmp = calloc(1, sizeof(linked_list_egg_t));
        if (tmp == NULL)
            return NULL;
        tmp->egg = calloc(1, sizeof(egg_t));
        if (tmp->egg == NULL)
            return NULL;
        tmp->egg->id = i;
        tmp->egg->x = rand() % info_game.width;
        tmp->egg->y = rand() % info_game.height;
        tmp->egg->team_name = info_game.team_names[i % info_game.nb_teams];
        tmp->next = egg_list;
        egg_list->prev = tmp;
        egg_list = tmp;
    }
    return egg_list;
}

static linked_list_egg_t *create_egg_list(info_game_t info_game)
{
    linked_list_egg_t *egg_list;

    egg_list = calloc(1, sizeof(linked_list_egg_t));
    if (egg_list == NULL)
        return NULL;
    egg_list->egg = calloc(1, sizeof(egg_t));
    if (egg_list->egg == NULL)
        return NULL;
    egg_list->next = NULL;
    egg_list->prev = NULL;
    egg_list->egg->id = 0;
    egg_list->egg->x = rand() % info_game.width;
    egg_list->egg->y = rand() % info_game.height;
    egg_list->egg->team_name = info_game.team_names[0];
    return get_all_eggs(info_game, egg_list);
}

static team_t *get_team(info_game_t info_game)
{
    team_t *teams = malloc(sizeof(team_t) * info_game.nb_teams);

    if (teams == NULL)
        return NULL;
    for (int i = 0; i < info_game.nb_teams; i++) {
        teams[i].name = info_game.team_names[i];
        teams[i].connected_clients = 0;
    }
    return teams;
}

in_game_t *init_game(info_game_t info_game)
{
    in_game_t *game = calloc(1, sizeof(in_game_t));

    if (game == NULL || info_game.nb_teams == 0)
        return NULL;
    game->map = get_tile(info_game.width, info_game.height);
    if (game->map == NULL) {
        free(game);
        return NULL;
    }
    game->teams = get_team(info_game);
    if (game->teams == NULL) {
        free(game->map);
        free(game);
        return NULL;
    }
    game->current_nb_players = 0;
    game->egg_list = create_egg_list(info_game);
    return game;
}
