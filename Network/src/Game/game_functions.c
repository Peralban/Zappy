/*
** EPITECH PROJECT, 2024
** game_functions.c
** File description:
** DESCRIPTION
*/

#include "Game/game_functions.h"
#include "Game/game.h"
#include <stdlib.h>

static void create_drone_list(tile_t *tile, drone_t *drone)
{
    tile->drone_list = malloc(sizeof(linked_list_drone_t));
    if (tile->drone_list == NULL)
        return;
    tile->drone_list->prev = NULL;
    tile->drone_list->drone = drone;
    tile->drone_list->next = NULL;
}

static void add_drone_at_pos(in_game_t *game, drone_t *drone)
{
    tile_t *tile = &game->map[drone->x][drone->y];
    linked_list_drone_t *tmp = NULL;

    if (tile->drone_list == NULL) {
        create_drone_list(tile, drone);
        return;
    }
    tmp = tile->drone_list;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(linked_list_drone_t));
    if (tmp->next == NULL)
        return;
    tmp->next->prev = tmp;
    tmp->next->drone = drone;
}

void create_player(server_t *server, client_t *client, char *team_name)
{
    drone_t *drone = calloc(1, sizeof(drone_t));
    static int all_id = 0;

    if (drone == NULL)
        return;
    drone->id = all_id;
    all_id++;
    drone->level = 1;
    drone->orientation = rand() % 4;
    drone->team_name = team_name;
    server->game->current_nb_players += 1;
    client->drone = drone;
    spawn_on_egg(server, drone, team_name);
    add_drone_at_pos(server->game, drone);
}

static linked_list_drone_t *found_drone(in_game_t *game, drone_t *drone)
{
    int coord[MAX_AXES] = {drone->x, drone->y};
    linked_list_drone_t *tmp = game->map[coord[X]][coord[Y]].drone_list;

    while (tmp != NULL) {
        if (tmp->drone == drone)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

static linked_list_drone_t *get_last_node(linked_list_drone_t *list)
{
    linked_list_drone_t *tmp = list;

    if (tmp == NULL)
        return NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    return tmp;
}

static void remove_drone_in_list(linked_list_drone_t **list, drone_t *drone)
{
    linked_list_drone_t *tmp = *list;

    while (tmp != NULL && tmp->drone != drone)
        tmp = tmp->next;
    if (tmp == NULL)
        return;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp == *list)
        *list = tmp->next;
    free(tmp);
}

static void exchange_drone(server_t *server, linked_list_drone_t *src,
    drone_t *drone)
{
    linked_list_drone_t *dest =
    get_last_node(server->game->map[drone->x][drone->y].drone_list);

    if (dest == NULL) {
        create_drone_list(&server->game->map[drone->x][drone->y], drone);
        return;
    }
    if (src->prev != NULL)
        src->prev->next = NULL;
    dest->next = src;
    src->prev = dest;
}

void move(drone_t *drone, server_t *server)
{
    int movement[] = {1, -1, 1, -1};
    int *coord[] = {&drone->y, &drone->y,
    &drone->x, &drone->x};
    int max[] = {server->info_game.height, server->info_game.height,
    server->info_game.width, server->info_game.width};
    linked_list_drone_t *src = found_drone(server->game, drone);
    int old[] = {drone->x, drone->y};

    if (src == NULL)
        return;
    *coord[drone->orientation] = (*coord[drone->orientation] +
    movement[drone->orientation] +
    max[drone->orientation]) % max[drone->orientation];
    remove_drone_in_list(&server->game->map[old[X]][old[Y]].drone_list, drone);
    exchange_drone(server, src, drone);
}

void turn(drone_t *drone, side_t side)
{
    drone->orientation = (drone->orientation + side) % 4;
}
