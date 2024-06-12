/*
** EPITECH PROJECT, 2024
** time_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

void time_request(server_t *server, client_t *client, char **args)
{
    char *reponse = calloc(128, sizeof(char));

    (void)args;
    sprintf(reponse, "sgt %d\n", server->info_game.freq);
    send(client->socket, reponse, strlen(reponse), 0);
    free(reponse);
}

void time_modification(server_t *server, client_t *client, char **args)
{
    char *reponse = calloc(128, sizeof(char));

    server->info_game.freq = atoi(args[1]);
    sprintf(reponse, "sgt %d\n", server->info_game.freq);
    send(client->socket, reponse, strlen(reponse), 0);
    free(reponse);
}
