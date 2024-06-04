/*
** EPITECH PROJECT, 2024
** game.h
** File description:
** DESCRIPTION
*/

#pragma once

/**
 * @struct tile_s
 * @brief Structure representing a tile in the game.
 */
typedef struct tile_s {
    item_t *items;
    drone_t *drone;
} tile_t;

/**
 * @struct team_s
 * @brief Structure representing a team in the game.
 */
typedef struct team_s {
    char *name;
    int connected_clients;
    drone_t *drone;
} team_t;

/**
 * @struct in_game_s
 * @brief Structure representing the state of the game.
 */
typedef struct in_game_s {
    tile_t **map;
    team_t *teams;
} in_game_t;
