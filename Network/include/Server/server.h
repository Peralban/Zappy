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
#include <signal.h>

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
    GRAPHIC
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
 * @brief Updates the game state.
 * @param server The server containing the game state to update.
 */
void game_tick(server_t *server);

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

/**
 * @brief finds a client by its drone id.
 * @param id The id of the drone to find.
 * @param server The server containing the clients.
 */
client_t *get_client_by_drone_id(int id, server_t *server);

/**
 * @brief removes a drone from the list of drones.
 * @param list The list of drones.
 * @param drone The drone to remove.
 */
void remove_drone_in_list(linked_list_drone_t **list, drone_t *drone);

/**
 * @brief resets a client to its initial state.
 * @param client The client to reset.
 * @param server The server containing the client.
 */
void reset_client(client_t *client, server_t *server);

/**
 * @brief Accepts a new client connection to the server.
 *
 * This function is responsible for accepting a new client connection
 * to the server.
 * It creates a new client object and adds it to the server's list of clients.
 *
 * @param server The server that the client is connecting to.
 */
void new_client(server_t *server);

/**
 * @brief Ends the server operation.
 *
 * This function is responsible for ending the server operation.
 * It closes all client connections and releases any resources
 * used by the server.
 *
 * @param server The server to end.
 * @return Returns 0 on successful execution and non-zero on failure.
 */
int end_server(server_t *server);

/**
 * @brief Replaces the global stop variable.
 *
 * This function is responsible for replacing the global stop variable.
 * It is used to control the server loop, stopping it when necessary.
 *
 * @param change The new value for the stop variable.
 * @warning if change is -1, the function will return the current
 * value of the stop variable. And will not change it.
 * @return The new value of the stop variable.
 */
sig_atomic_t replace_stop(int change);
