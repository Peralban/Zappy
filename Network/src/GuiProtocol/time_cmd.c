/*
** EPITECH PROJECT, 2024
** time_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

void time_request(client_t *client, server_t *server, char **args)
{
    char *reponse = calloc(128, sizeof(char));

    (void)args;
    sprintf(reponse, "sgt %d\n", server->info_game.freq);
    send(client->socket, reponse, strlen(reponse), 0);
    free(reponse);
}

void time_modification(client_t *client, server_t *server, char **args)
{
    char *reponse = calloc(128, sizeof(char));

    server->info_game.freq = atoi(args[0]);
    sprintf(reponse, "sgt %d\n", server->info_game.freq);
    send(client->socket, reponse, strlen(reponse), 0);
    free(reponse);
}
