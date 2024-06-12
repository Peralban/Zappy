/*
** EPITECH PROJECT, 2024
** time_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"
#include "GuiProtocol/gui_event.h"

static bool is_number(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

void gui_sst(server_t *server)
{
    char buffer[1024] = {0};

    sprintf(buffer, "sst %d\n", server->info_game.freq);
    send_all_graphics(server, buffer);
}

void time_request(client_t *client, server_t *server, char **args)
{
    char response[1024] = {0};

    (void)args;
    sprintf(response, "sgt %d\n", server->info_game.freq);
    send(client->socket, response, strlen(response), 0);
}

void time_modification(client_t *client, server_t *server, char **args)
{
    server->info_game.freq = atoi(args[0]);
    if (server->info_game.freq < 1 || !is_number(args[0])) {
        send(client->socket, "sbp\n", 4, 0);
        return;
    }
    gui_sst(server);
}
