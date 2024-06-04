/*
** EPITECH PROJECT, 2024
** game.h
** File description:
** DESCRIPTION
*/

#pragma once

/**
 * @enum orientation_e
 * @brief Enumeration representing the orientation of a drone.
 */
typedef enum orientation_e {
    NORTH,
    EAST,
    SOUTH,
    WEST
} orientation_t;

/**
 * @struct item_s
 * @brief Structure representing an item in the game.
 */
typedef struct item_s {
    char *name;
    int quantity;
} item_t;

/**
 * @struct drone_s
 * @brief Structure representing a drone in the game.
 */
typedef struct drone_s {
    orientation_t orientation;
    int id;
    int level;
    int inventory[7];
} drone_t;

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

/**
 * @brief Initializes the game with the provided game information.
 * @param info_game The game information to initialize the game with.
 * @return A pointer to the initialized game.
 */
in_game_t *init_game(info_game_t info_game);
