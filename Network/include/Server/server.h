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

#define EXIT_FAIL 84
#define EXIT_SUCC 0

typedef enum {
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

typedef struct client_server_s {
    int socket;
    struct sockaddr_in *clientAddress;
} client_server_t;

typedef struct client_s {
    client_server_t *clientServer;
} client_t;

typedef struct client_list_s {
    client_t *client;
    struct client_list_s *next;
    struct client_list_s *prev;
} client_list_t;

typedef struct info_game_s {
    int width;
    int height;
    char **team_names;
    int clientsNb;
    int freq;
} info_game_t;

typedef struct server_s {
    fd_set readfds;
    fd_set writefds;
    int port;
    int socket;
    struct sockaddr_in *serverAddress;
    info_game_t *info_game;
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
int zappy_network(int ac, char **av);

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
 */
void check_return_value(int value_to_check, error_type_t error_type);

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
