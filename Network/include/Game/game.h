/*
** EPITECH PROJECT, 2024
** game.h
** File description:
** DESCRIPTION
*/

#pragma once

/**
 * @enum axes_e
 * @brief Enumeration representing the axes of the game.
 */
typedef enum {
    X,
    Y,
    MAX_AXES
} axes_t;

/**
 * @enum orientation_e
 * @brief Enumeration representing the orientation of a drone.
 */
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} orientation_t;

/**
 * @enum crystal_type_e
 * @brief Enumeration representing the type of a crystal.
 */
typedef enum{
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    MAX_ITEMS
} item_type_t;

/**
 * @enum side_e
 * @brief Enumeration representing the side of a drone.
 */
typedef enum {
    LEFT = 1,
    RIGHT = 3
} side_t;

/**
 * @struct item_s
 * @brief Structure representing an item in the game.
 */
typedef int inventory_t[MAX_ITEMS];

typedef struct server_s server_t;

/**
 * @struct drone_s
 * @brief Structure representing a drone in the game.
 */
typedef struct drone_s {
    /*----- Data -----*/
    orientation_t orientation;
    int id;
    int level;
    int x;
    int y;
    inventory_t inventory;
    char *team_name;
    int ticks;
} drone_t;

/**
 * @struct linked_list_drone_s
 * @brief Structure representing a linked list of drones.
 */
typedef struct linked_list_drone_s {
    drone_t *drone;
    struct linked_list_drone_s *next;
    struct linked_list_drone_s *prev;
} linked_list_drone_t;

/**
 * @struct tile_s
 * @brief Structure representing a tile in the game.
 */
typedef struct tile_s {
    inventory_t inventory;
    linked_list_drone_t *drone_list;
} tile_t;

/**
 * @struct team_s
 * @brief Structure representing a team in the game.
 */
typedef struct team_s {
    char *name;
    int connected_clients;
} team_t;

/**
 * @struct in_game_s
 * @brief Structure representing the state of the game.
 */
typedef struct in_game_s {
    tile_t **map;
    team_t *teams;
    int current_nb_players;
} in_game_t;
