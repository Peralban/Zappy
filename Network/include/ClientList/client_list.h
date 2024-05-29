/*
** EPITECH PROJECT, 2024
** Clientlist.h
** File description:
** DESCRIPTION
*/

#pragma once

#include "Server/server.h"

/**
 * @brief Creates a new client list.
 *
 * This function creates a new client list and returns a pointer to it.
 *
 * @return A pointer to the newly created client list.
 */
client_list_t *create_client_list(void);

/**
 * @brief Creates a new client.
 *
 * This function creates a new client with the given socket and server address.
 *
 * @param socket The socket of the client.
 * @param serverAddress The server address of the client.
 * @return A pointer to the newly created client.
 */
client_t *create_client(int socket, struct sockaddr_in *Address);

/**
 * @brief Adds a client to a client list.
 *
 * This function adds a given client to a given client list.
 *
 * @param list A pointer to the client list.
 * @param client A pointer to the client to be added.
 * @return 0 if the client was added successfully, -1 otherwise.
 */
int add_client_to_list(client_list_t **list, client_t *client);

/**
 * @brief Removes a client from a client list.
 *
 * This function removes a given client from a given client list.
 *
 * @param list A pointer to the client list.
 * @param client A pointer to the client to be removed.
 */
void remove_client_from_list(client_list_t **list, client_t *client);

/**
 * @brief Retrieves a client from a client list by socket.
 *
 * This function retrieves a client from a given client list using the client's
 * socket.
 *
 * @param list A pointer to the client list.
 * @param socket The socket of the client to be retrieved.
 * @return A pointer to the client if found, NULL otherwise.
 */
client_t *get_client_from_list(client_list_t *list, int socket);

/**
 * @brief Frees a client list.
 *
 * This function frees a given client list.
 *
 * @param list A pointer to the client list to be freed.
 */
void destroy_client_list(client_list_t *list);

/**
 * @brief Removes a client from a server.
 *
 * This function removes a given client from a given server.
 *
 * @param client A pointer to the client to be removed.
 * @param list A pointer to the client list.
 * @param server A pointer to the server.
 */
void eject_client_from_server(client_t *client, client_list_t **list,
    server_t **server);
