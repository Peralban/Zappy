/*
** EPITECH PROJECT, 2024
** move_args_to_server_struct.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Parsing/arguments_struct.h"
#include "lib/my.h"

bool complete_integer_data(server_t *server, char **args)
{
    server->port = atoi(args[PORT]);
    if (server->port <= 0)
        printf("Port must be a positive number\n");
    server->info_game.width = atoi(args[WIDTH]);
    if (server->info_game.width <= 0)
        printf("Width must be a positive number\n");
    server->info_game.height = atoi(args[HEIGHT]);
    if (server->info_game.height <= 0)
        printf("Height must be a positive number\n");
    server->info_game.nb_client = atoi(args[CLIENTS_NB]);
    if (server->info_game.nb_client <= 0)
        printf("Number of clients must be a positive number\n");
    server->info_game.freq = atoi(args[FREQ]);
    if (server->info_game.freq <= 0)
        printf("Frequency must be a positive number\n");
    if (server->port <= 0 || server->info_game.width <= 0 ||
    server->info_game.height <= 0 || server->info_game.nb_client <= 0 ||
    server->info_game.freq <= 0)
        return true;
    return false;
}

server_t *move_args_to_server_struct(char **args)
{
    server_t *server = calloc(1, sizeof(server_t));
    bool return_null = 0;

    if (server == NULL || args == NULL || args[NAMES] == NULL)
        return NULL;
    server->info_game.team_names = my_str_to_word_array(args[NAMES], " ");
    if (server->info_game.team_names == NULL) {
        printf("Error while parsing names\n");
        return_null = true;
    }
    if (return_null || complete_integer_data(server, args)) {
        if (server->info_game.team_names != NULL)
            my_free_array(server->info_game.team_names);
        free(server);
        free(args);
        return NULL;
    }
    free(args);
    return server;
}
