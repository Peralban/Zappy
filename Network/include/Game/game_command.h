/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "game.h"
#include "game_functions.h"
#include <stdio.h>

/**
 * @brief Moves the client's character forward in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void forward(client_t *client, server_t *server, char *args);
void incantation(client_t *client, server_t *server);

/**
 * @brief Turns the client's character to the right in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void right(client_t *client, server_t *server, char *args);

/**
 * @brief Turns the client's character to the left in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void left(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to look around in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void look(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to check their inventory in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void inventory(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to broadcast a message in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void broadcast(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to fork a new player in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void fork_player(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to check the number of unused
 * connections in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void connect_nbr(client_t *client, server_t *server, char *args);

/**
 * @brief Allows the client's character to eject other players from
 * their tile in the game.
 *
 * @param client The client who is playing the game.
 * @param server The server where the game is hosted.
 * @param args The arguments for the command.
 */
void eject(client_t *client, server_t *server, char *args);

static const inventory_t incantation_level_prerequisites[7] = {
        {1, 1, 0, 0, 0, 0, 0},
        {2, 1, 1, 1, 0, 0, 0},
        {2, 2, 0, 1, 0, 2, 0},
        {4, 1, 1, 2, 0, 1, 0},
        {4, 1, 2, 1, 3, 0, 0},
        {6, 1, 2, 3, 0, 1, 0},
        {6, 2, 2, 2, 2, 2, 1},
};

bool check_incantation_condition(client_t *client, server_t *server);

/**
 * @brief A structure to represent a game command.
 *
 * @param name The name of the command.
 * @param function The function to execute the command.
 * @param duration The duration of the command.
 * @param nb_args The number of arguments for the command.
 */
typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char *arg);
    bool (*condition)(client_t *client, server_t *server);
    int duration;
    int nb_args;
} command_t;

/**
 * @brief An array of game commands.
 *
 * This array includes the commands
 * "Forward", "Right", "Left", "Look", "Inventory", and "Broadcast".
 */
static const command_t commands_opt[] = {
    {"Forward", &forward, 7, 0},
    {"Right", &right, 7, 0},
    {"Left", &left, 7, 0},
    {"Look", &look, 7, 0},
    {"Inventory", &inventory, 1, 0},
    {"Broadcast", &broadcast, 7, 1},
    {"Fork", &fork_player, 42, 0},
    {"Connect_nbr", &connect_nbr, 7, 0},
    {"Eject", &eject, 7, 0},
    {"Incantation", &incantation, &check_incantation_condition, 300},
    {NULL, NULL, 0, 0}
};
