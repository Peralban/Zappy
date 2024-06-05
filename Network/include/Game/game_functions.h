/*
** EPITECH PROJECT, 2024
** game_functions.h
** File description:
** DESCRIPTION
*/

#pragma once

#include "Server/server.h"
#include "Server/game.h"

/**
 * @brief Creates a new player in the game.
 *
 * @param server The server object containing the game state.
 * @param client The client object representing the new player.
 * @param team_name The name of the team the player is joining.
 */
void create_player(server_t *server, client_t *client, char *team_name);

/**
 * @brief Turns a drone to a specified side.
 *
 * @param drone The drone to turn.
 * @param side The side to turn the drone to.
 */
void turn(drone_t *drone, side_t side);

/**
 * @brief Moves a drone in a specified direction.
 *
 * @param drone The drone to move.
 * @param dir The direction to move the drone in.
 * @param server The server object containing the game state.
 */
void move(drone_t *drone, direction_t dir, server_t *server);

/**
 * @brief Adds a drone at a specific position in the game.
 *
 * @param game The game object.
 * @param drone The drone to add.
 */
void add_drone_at_pos(in_game_t *game, drone_t *drone);

/**
 * @brief Gets the last node in a linked list of drones.
 *
 * @param list The linked list of drones.
 * @return The last node in the linked list.
 */
linked_list_drone_t *get_last_node(linked_list_drone_t *list);
