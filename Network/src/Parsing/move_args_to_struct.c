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
    int *data[] = {&server->port, &server->info_game.width,
    &server->info_game.height, &server->info_game.nb_client,
    &server->info_game.freq};
    char *messages[] = {"Port", "Width",
    "Height", "Number of clients", "Frequency"};
    args_name_t args_index[] = {PORT, WIDTH, HEIGHT, CLIENTS_NB, FREQ};
    bool is_valid = true;

    for (int i = 0; i < 5; i++) {
        *data[i] = atoi(args[args_index[i]]);
        if (*data[i] <= 0) {
            printf("%s must be a positive number\n", messages[i]);
            is_valid = false;
        }
    }
    return is_valid;
}

static server_t *get_server(char **args, server_t *server, bool return_null)
{
    if (!complete_integer_data(server, args))
        return_null = true;
    server->game = init_game(server->info_game);
    if (return_null || server->game == NULL) {
        if (server->info_game.team_names != NULL)
            my_free_array(server->info_game.team_names);
        free(server);
        free(args);
        return NULL;
    }
    free(args);
    return server;
}

server_t *move_args_to_server_struct(char **args)
{
    server_t *server = calloc(1, sizeof(server_t));
    bool return_null = 0;

    if (server == NULL || args == NULL || args[NAMES] == NULL)
        return NULL;
    server->info_game.team_names = my_str_to_word_array(args[NAMES], " ");
    server->info_game.nb_teams = my_array_len(server->info_game.team_names);
    if (server->info_game.team_names == NULL) {
        printf("Error while parsing names\n");
        return_null = true;
    }
    return get_server(args, server, return_null);
}
