/*
** EPITECH PROJECT, 2024
** game_functions.c
** File description:
** DESCRIPTION
*/

#include "game_functions.h"
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
    drone->x = rand() % server->game->info_game.width;
    drone->y = rand() % server->game->info_game.height;
    drone->team_name = team_name;
    server->game->current_nb_players += 1;
    client->drone = drone;
    add_drone_at_pos(server->game, drone);
}

void move(drone_t *drone, direction dir, info_game_t *info_game)
{
    int movement = dir == FORWARD ? 1 : -1;

    if (drone->orientation == NORTH && drone->y + movement < info_game->height)
        drone->y += movement;
    if (drone->orientation == SOUTH && drone->y - movement >= 0)
        drone->y -= movement;
    if (drone->orientation == EAST && drone->x + movement < info_game->width)
        drone->x += movement;
    if (drone->orientation == WEST && drone->x - movement >= 0)
        drone->x -= movement;
}