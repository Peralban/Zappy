/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Server/server.h"

static void send_all_eggs(server_t *server, client_t *client)
{
    linked_list_egg_t *list = server->game->egg_list;
    char buffer[1024] = {0};

    while (list != NULL) {
        sprintf(buffer, "enw %d %d %d %d\n", list->egg->id, -1,
            list->egg->x, list->egg->y);
        send(client->socket, buffer, strlen(buffer), 0);
        list = list->next;
    }
}

static void send_all_players(server_t *server, client_t *client)
{
    client_list_t *tmp = server->list;
    char buffer[1024] = {0};

    while (tmp != NULL) {
        if (tmp->client && tmp->client->state == PLAYING) {
            sprintf(buffer, "pnw %d %d %d %d %d %s\n", tmp->client->drone->id,
                tmp->client->drone->x, tmp->client->drone->y,
                tmp->client->drone->orientation, tmp->client->drone->level,
                tmp->client->drone->team_name);
            send(client->socket, buffer, strlen(buffer), 0);
        }
        tmp = tmp->next;
    }
}

void start_gui_client(server_t *server, client_t *client)
{
    char buffer[1024] = {0};

    if (client->state != GRAPHIC)
        return;
    sprintf(buffer, "msz %d %d\n", server->info_game.width,
        server->info_game.height);
    send(client->socket, buffer, strlen(buffer), 0);
    send_all_eggs(server, client);
    send_all_players(server, client);
}
