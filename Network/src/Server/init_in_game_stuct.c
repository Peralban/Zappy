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
    tile_t **tile = calloc(x, sizeof(tile_t *));

    if (tile == NULL)
        return NULL;
    for (int i = 0; i < x; i++) {
        tile[i] = calloc(y, sizeof(tile_t));
        if (tile[i] == NULL)
            return NULL;
    }
    return tile;
}

egg_t *create_egg(char *team_name, int x, int y)
{
    egg_t *egg = calloc(1, sizeof(egg_t));
    static int id = 0;

    if (egg == NULL)
        return NULL;
    egg->id = id;
    id++;
    egg->x = x;
    egg->y = y;
    egg->team_name = team_name;
    return egg;
}

static linked_list_egg_t *get_all_eggs(info_game_t info_game,
    linked_list_egg_t *egg_list)
{
    linked_list_egg_t *tmp;

    for (int i = 1; i < info_game.nb_client * info_game.nb_teams; i++) {
        tmp = calloc(1, sizeof(linked_list_egg_t));
        if (tmp == NULL)
            return NULL;
        tmp->egg = create_egg(info_game.team_names[i % info_game.nb_teams],
            rand() % info_game.width, rand() % info_game.height);
        if (tmp->egg == NULL)
            return NULL;
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
    egg_list->next = NULL;
    egg_list->prev = NULL;
    egg_list->egg = create_egg(info_game.team_names[0], rand() % info_game.width,
        rand() % info_game.height);
    if (egg_list->egg == NULL)
        return NULL;
    return get_all_eggs(info_game, egg_list);
}

static team_t *get_team(info_game_t info_game)
{
    team_t *teams = malloc(sizeof(team_t) * info_game.nb_teams);

    if (teams == NULL)
        return NULL;
    for (int i = 0; i < info_game.nb_teams; i++) {
        teams[i].name = info_game.team_names[i];
        teams[i].nb_egg = info_game.nb_client;
    }
    return teams;
}

static void init_ressources(info_game_t info_game, in_game_t *game)
{
    double ressources_quantity[MAX_ITEMS] = {DENSITY_FOOD, DENSITY_LINEMATE,
        DENSITY_DERAUMERE, DENSITY_SIBUR, DENSITY_MENDIANE, DENSITY_PHIRAS,
        DENSITY_THYSTAME};
    int x;
    int y;

    for (int k = 0; k < MAX_ITEMS; k++) {
        ressources_quantity[k] *= info_game.width * info_game.height;
        if (ressources_quantity[k] < 1)
            ressources_quantity[k] = 1;
        for (int n = 0; n < ressources_quantity[k]; n++) {
            x = rand() % info_game.width;
            y = rand() % info_game.height;
            game->map[x][y].inventory[k] += 1;
        }
    }
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
    init_ressources(info_game, game);
    game->egg_list = create_egg_list(info_game);
    return game;
}
