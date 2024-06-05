/*
** EPITECH PROJECT, 2024
** game_functions.c
** File description:
** DESCRIPTION
*/

#include "Game/game_functions.h"
#include "Server/game.h"
#include <stdlib.h>

static void create_drone_list(tile_t **tile, drone_t *drone)
{
    (*tile)->drone_list = malloc(sizeof(linked_list_drone_t));
    if ((*tile)->drone_list == NULL)
        return;
    (*tile)->drone_list->prev = NULL;
    (*tile)->drone_list->drone = drone;
    (*tile)->drone_list->next = NULL;
}

void add_drone_at_pos(in_game_t *game, drone_t *drone)
{
    tile_t *tile = &game->map[drone->x][drone->y];

    if (tile->drone_list == NULL) {
        create_drone_list(&tile, drone);
        return;
    }
    linked_list_drone_t *tmp = tile->drone_list;
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
    drone_t *drone = malloc(sizeof(drone_t));
    static int id = 0;

    if (drone == NULL)
        return;
    drone->id = id++;
    drone->level = 1;
    drone->orientation = rand() % 4;
    drone->x = rand() % server->info_game.width;
    drone->y = rand() % server->info_game.height;
    drone->team_name = team_name;
    server->game->current_nb_players += 1;
    client->drone = drone;
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

linked_list_drone_t *get_last_node(linked_list_drone_t *list)
{
    linked_list_drone_t *tmp = list;

    while (tmp->next != NULL)
        tmp = tmp->next;
    return tmp;
}

void move(drone_t *drone, direction_t dir, server_t *server)
{
    int movement = dir == FORWARD ? 1 : -1;
    int max_coord[MAX_AXES] = {server->info_game.width,
    server->info_game.height};
    linked_list_drone_t *src = found_drone(server->game, drone);
    linked_list_drone_t *dest = NULL;

    if (src == NULL)
        return;
    if (drone->orientation == NORTH && drone->y + movement < max_coord[Y])
        drone->y += movement;
    if (drone->orientation == SOUTH && drone->y - movement >= 0)
        drone->y -= movement;
    if (drone->orientation == EAST && drone->x + movement < max_coord[X])
        drone->x += movement;
    if (drone->orientation == WEST && drone->x - movement >= 0)
        drone->x -= movement;
    dest = get_last_node(server->game->map[drone->x][drone->y].drone_list);
    src->prev->next = NULL;
    dest->next = src;
    src->prev = dest;
}

void turn(drone_t *drone, side_t side)
{
    drone->orientation = (drone->orientation + side) % 4;
}
