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

/**
 * @brief Allows a drone to observe its surroundings.
 *
 * This function is used to let a drone look around in the game.
 * It could be used to gather information about the game state,
 * such as the positions of other drones, obstacles, or points of interest.
 *
 * @param drone The drone that is looking around.
 * @param server The server object containing the game state.
 * @return char * The sentence to send to the client.
 */
char *look_around(drone_t *drone, server_t *server);

/**
 * @brief Displays the inventory of a drone.
 *
 * This function is used to retrieve and format the inventory of a
 * drone in the game.
 * It could be used to provide information about the drone's
 * current resources to the client.
 *
 * @param drone The drone whose inventory is to be displayed.
 * @return char* A string representation of the drone's inventory.
 */
char *display_inventory(drone_t *drone);

/**
 * @brief Launches the broadcast of a message from a drone.
 *
 * This function is used to launch the broadcast of a message
 * from a drone to all other drones in the game.
 * It could be used to communicate information or commands
 * from one drone to others.
 *
 * @param drone The drone that is broadcasting the message.
 * @param server The server object containing the game state.
 * @param args The message to be broadcasted.
 * @return bool if broadcast fail
 */
bool launch_broadcast(drone_t *drone, server_t *server, char *args);

/**
 * @brief Allows the client's character to drop an object in the game.
 *
 * This function is used to drop an object from the client's character's inventory.
 * It could be used when the character needs to free up inventory space or leave an
 * object for another character.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command, which should include the name of the
 * object to drop.
 * @return Returns true if the object was successfully dropped, false otherwise.
 */
bool drop_object(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to take an object in the game.
 *
 * This function is used to pick up an object from the game world and add it to the
 * client's character's inventory.
 * It could be used when the character finds a useful object during their
 * exploration.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command, which should include
 * the name of the object to take.
 * @return Returns true if the object was successfully taken,
 * false otherwise.
 */
bool take_object(client_t *client, server_t *server, char *args);
