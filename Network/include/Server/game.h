/*
** EPITECH PROJECT, 2024
** game.h
** File description:
** DESCRIPTION
*/

#pragma once

typedef struct tile_s {
    item_t *items;
    drone_t *drone;
} tile_t;

typedef struct team_s {
    char *name;
    int connected_clients;
    drone_t *drone;
} team_t;

typedef struct in_game_s {
    tile_t **map;
    team_t *teams;
} in_game_t;
