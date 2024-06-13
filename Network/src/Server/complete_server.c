/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** complete_server.c
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include "lib/my.h"

void new_client(server_t *server)
{
    struct sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);
    int client_socket = accept(server->socket,
    (struct sockaddr *) &client_address, &client_address_length);

    if (!check_return_value(client_socket, ACCEPT))
        return;
    add_client_to_list(server->list, create_client(client_socket));
    FD_SET(client_socket, &server->readfds);
    FD_SET(client_socket, &server->writefds);
    send(client_socket, "WELCOME\n", 8, 0);
}

static void free_client_player(client_t *client)
{
    free(client->drone);
    for (int i = 0; client->command[i] != NULL; i++)
        free(client->command[i]);
}

static void free_client_gui(client_t *client)
{
    for (int i = 0; client->command[i] != NULL; i++)
        free(client->command[i]);
}

static void free_egg_list(linked_list_egg_t *egg_list)
{
    linked_list_egg_t *tmp = egg_list;
    linked_list_egg_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->egg);
        free(tmp);
        tmp = next;
    }
}

static void free_in_game(in_game_t *game, info_game_t info_game)
{
    for (int i = 0; i < info_game.width; i++) {
        for (int j = 0; j < info_game.height; j++)
            free(game->map[i][j].drone_list);
        free(game->map[i]);
    }
    free(game->map);
    free(game->teams);
    free_egg_list(game->egg_list);
    free(game);
}

sig_atomic_t replace_stop(int change)
{
    static volatile sig_atomic_t stop = 0;

    if (change != -1)
        stop = change;
    return stop;
}

int end_server(server_t *server)
{
    client_list_t *tmp2 = NULL;

    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp2 != NULL)
            free(tmp2);
        if (tmp->client->state == PLAYING)
            free_client_player(tmp->client);
        if (tmp->client->state == GRAPHIC)
            free_client_gui(tmp->client);
        eject_client_from_server(tmp->client, server);
        tmp2 = tmp;
    }
    if (tmp2 != NULL)
        free(tmp2);
    free_in_game(server->game, server->info_game);
    my_free_array(server->info_game.team_names);
    free(server->serverAddress);
    close(server->socket);
    free(server);
    return 0;
}
