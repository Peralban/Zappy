/*
** EPITECH PROJECT, 2024
** game_functions.h
** File description:
** DESCRIPTION
*/

#pragma once

#include "Server/server.h"
#include "game.h"

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
 * @param server The server object containing the game state.
 * @param orientation The direction to move the drone in.
 */
void move(drone_t *drone, server_t *server, orientation_t orientation);

/**
 * @brief Spawns a drone on an egg.
 *
 * @param server The server object containing the game state.
 * @param drone The drone to spawn.
 * @param team_name The name of the team the drone is joining.
 */
void spawn_on_egg(server_t *server, drone_t *drone, char *team_name);

/**
 * @brief Removes an egg from the egg list.
 *
 * @param egg The egg to remove.
 * @param list The list of eggs to remove the egg from.
 */
void remove_egg_elem(linked_list_egg_t *egg, linked_list_egg_t **list);
