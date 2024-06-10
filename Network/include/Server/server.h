/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** client.h
*/

#pragma once

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Game/game.h"

#define EXIT_FAIL 84
#define EXIT_SUCC 0
#define MAX_COMMAND 10

/**
 * @brief Enum for the different types of errors that may occur.
 * @warning The NONE type is used as a default value.
 */
typedef enum error_type_e {
    SOCKET,
    SETSOCKOPT,
    BIND,
    LISTEN,
    SELECT,
    CONNECT,
    ACCEPT,
    READ,
    WRITE,
    CLOSE,
    FORK,
    CHDIR,
    RECV,
    SEND
} error_type_t;

typedef enum client_state_e {
    WAITING,
    PLAYING,
} client_state_t;

typedef struct drone_s drone_t;

/**
 * @struct client_s
 * @brief Structure representing a client.
 */
typedef struct client_s {
    int socket;
    client_state_t state;
    drone_t *drone;
    char *command[MAX_COMMAND];
} client_t;

/**
 * @struct client_list_s
 * @brief Structure representing a list of clients.
 */
typedef struct client_list_s {
    client_t *client;
    struct client_list_s *next;
    struct client_list_s *prev;
} client_list_t;

/**
 * @struct info_game_s
 * @brief Structure representing game information.
 */
typedef struct info_game_s {
    int width;
    int height;
    int nb_teams;
    char **team_names;
    int nb_client;
    int freq;
} info_game_t;

/**
 * @struct server_s
 * @brief Structure representing a server.
 */
typedef struct server_s {
    fd_set readfds;
    fd_set writefds;
    int port;
    int socket;
    struct sockaddr_in *serverAddress;
    client_list_t *list;
    info_game_t info_game;
    in_game_t *game;
} server_t;

/**
 * @brief Entry point for the FTP server.
 *
 * This function serves as the entry point for the FTP server. It takes command
 * line arguments
 * as parameters, which could be used for configuration purposes.
 *
 * @param ac The count of command line arguments.
 * @param av The array of command line arguments.
 * @return Returns 0 on successful execution and non-zero on failure.
 */
int zappy_network(char **args);

/**
 * @brief Checks the return value of a function and handles errors.
 *
 * This function checks the return value of a function and handles any errors
 * that may have occurred.
 * If the return value indicates an error, the function prints an error message
 * corresponding to the error type and exits the program.
 *
 * @param value_to_check The return value to check.
 * @param error_type The type of error that may have occurred.
 * @return Returns true if the value is an error, false otherwise.
 */
bool check_return_value(int value_to_check, error_type_t error_type);

/**
 * @brief Main loop for the FTP server.
 *
 * This function serves as the main loop for the FTP server. It takes the
 * server socket and server address
 * as parameters, and continuously listens for and handles client connections.
 *
 * @param server_socket The socket of the server.
 * @return Returns 0 on successful execution and non-zero on failure.
 */
int server_loop(server_t *server);

/**
 * @brief Initializes the game with the provided game information.
 * @param info_game The game information to initialize the game with.
 * @return A pointer to the initialized game.
 */
in_game_t *init_game(info_game_t info_game);

/**
 * @brief Updates the players in the game.
 * @param server The server containing the players to update.
 */
void update_players(server_t *server);

/**
 * @brief sets the number of ticks to wait for
 * the client to execute its next command.
 * @param client The client to set the ticks for.
 */
void set_ticks(client_t *client);
/**
 * @brief Creates a new egg in the game.
 * @param team_name The name of the team that the egg belongs to.
 * @param x The x-coordinate of the egg.
 * @param y The y-coordinate of the egg.
 * @return A pointer to the created egg.
 */
egg_t *create_egg(char *team_name, int x, int y);
