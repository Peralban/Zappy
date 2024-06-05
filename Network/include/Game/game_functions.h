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
 */
void move(drone_t *drone, server_t *server);

/**
 * @brief Allows a drone to observe its surroundings.
 *
 * This function is used to let a drone look around in the game. It could be used to gather information about the game state,
 * such as the positions of other drones, obstacles, or points of interest.
 *
 * @param drone The drone that is looking around.
 * @param server The server object containing the game state.
 */
void look_around(drone_t *drone, server_t *server);
