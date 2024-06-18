/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"

/**
 * @brief Executes admin commands.
 *
 * This function is responsible for executing admin commands.
 * It takes a client, server, and buffer as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param buffer The buffer containing the command to be executed.
 */
void exec_admin_commands(client_t *client, server_t *server, char *buffer);

/**
 * @brief Pauses the game.
 *
 * This function is responsible for pausing the game.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_pause(client_t *client, server_t *server, char **args);

/**
 * @brief Sets the frequency of the game.
 *
 * This function is responsible for setting the frequency of the game.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_set_freq(client_t *client, server_t *server, char **args);

/**
 * @brief Ticks the game.
 *
 * This function is responsible for ticking the game.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_tick(client_t *client, server_t *server, char **args);

/**
 * @brief Levels up a player.
 *
 * This function is responsible for leveling up a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_level_up(client_t *client, server_t *server, char **args);

/**
 * @brief Levels down a player.
 *
 * This function is responsible for leveling down a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_level_down(client_t *client, server_t *server, char **args);

/**
 * @brief Sets the level of a player.
 *
 * This function is responsible for setting the level of a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_set_level(client_t *client, server_t *server, char **args);

/**
 * @brief Teleports a player.
 *
 * This function is responsible for teleporting a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_tp(client_t *client, server_t *server, char **args);

/**
 * @brief Sets the inventory of a player.
 *
 * This function is responsible for setting the inventory of a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_set_inventory(client_t *client, server_t *server, char **args);

/**
 * @brief Locates a player.
 *
 * This function is responsible for locating a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_locate(client_t *client, server_t *server, char **args);

/**
 * @brief Provides help for admin commands.
 *
 * This function is responsible for providing help for admin commands.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_help(client_t *client, server_t *server, char **args);

/**
 * @brief Gets the inventory of a player.
 *
 * This function is responsible for getting the inventory of a player.
 * It takes a client, server, and arguments as parameters.
 *
 * @param client The client who is executing the command.
 * @param server The server where the command is executed.
 * @param args The arguments of the command.
 */
void adm_get_inventory(client_t *client, server_t *server, char **args);

typedef struct {
    char *name;
    void (*function)(client_t *client, server_t *server, char **args);
    int nb_args;
} command_admin_t;

static const command_admin_t commands_admin[] = {
    {"/pause", adm_pause, 0},
    {"/set_freq", adm_set_freq, 1},
    {"/tick", adm_tick, 2},
    {"/levelup", adm_level_up, 1},
    {"/leveldown", adm_level_down, 1},
    {"/setlevel", adm_set_level, 2},
    {"/tp", adm_tp, 3},
    {"/setinventory", adm_set_inventory, 8},
    {"/locate", adm_locate, 1},
    {"/getinventory", adm_get_inventory, 1},
    {"/help", adm_help, 0},
    {NULL, NULL, 0}
};

typedef struct {
    char type;
    char *type_str;
    int multiplier;
} tick_command_admin_t;

static const tick_command_admin_t tick_commands_admin[] = {
    {'t', "ticks", 0},
    {'s', "seconds", 1},
    {'m', "minutes", 60},
    {'h', "hours", 60 * 60},
    {'d', "days", 60 * 60 * 24},
    {0, NULL, 0}
};

/**
 * @brief Prints and sends a message.
 *
 * This function is responsible for printing and sending a message. It takes a message and a client as parameters.
 *
 * @param msg The message to be printed and sent.
 * @param client The client to whom the message is sent.
 */
void print_and_send(char *msg, client_t *client);

/**
 * @brief Gets a drone by its ID.
 *
 * This function is responsible for getting a drone by its ID. It takes a server and an ID as parameters.
 *
 * @param server The server where the drone is located.
 * @param id The ID of the drone.
 * @return The drone with the given ID.
 */
client_list_t *get_drone_by_id(server_t *server, int id);
