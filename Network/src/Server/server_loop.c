/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** server_loop.c
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include "Game/game_functions.h"
#include "Game/game_command.h"
#include "lib/my.h"
#include <stdio.h>

static void start_communication_with_client(client_t *client,
    server_t *server, char *buffer)
{
    for (int i = 0; server->info_game.team_names[i] != NULL; i++) {
        if (strcmp(buffer, server->info_game.team_names[i]) == 0 &&
            server->game->teams[i].connected_clients <
            server->info_game.nb_client) {
            server->game->teams[i].connected_clients++;
            sprintf(buffer, "%d\n%d %d\n",
                server->info_game.nb_client -
                server->game->teams[i].connected_clients,
                server->info_game.width, server->info_game.height);
            send(client->socket, buffer, strlen(buffer), 0);
            client->state = CONNECTED;
            create_player(server, client, server->info_game.team_names[i]);
            return;
        }
    }
    send(client->socket, "ko\n", 3, 0);
}

static void new_client(server_t *server)
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

static void parse_command_nam(server_t *server, client_t *client, char *buffer)
{
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(buffer, commands[i].name) == 0) {
            commands[i].function(client->drone, server);
            send(client->socket, "ok\n", 3, 0);
            return;
        }
    }
    send(client->socket, "ko\n", 3, 0);
}

static void parse_command(server_t *server, client_t *client, char *buffer)
{
    char **commands_arr = my_str_to_word_array(buffer, "\n");
    for (int i = 0; commands_arr[i] != NULL; i++) {
        parse_command_nam(server, client, commands_arr[i]);
    }
}

// the send is temporary, it will be deplaced in another function.
// the "quit" command may be temporary.
static void recv_command(client_t *client, server_t *server)
{
    char buffer[1024];
    int buffer_length;

    buffer_length = (int)recv(client->socket, buffer, 1024, 0);
    if (!check_return_value(buffer_length, RECV))
        return;
    buffer[buffer_length - 2] = '\0';
    printf("Received: %s\n", buffer);
    if (strcmp(buffer, "quit") == 0)
        eject_client_from_server(client, server);
    else if (client->state == WAITING)
        start_communication_with_client(client, server, buffer);
    else
        parse_command(server, client, buffer);
}

static void client_already_connected(server_t *server)
{
    for (client_list_t *tmp = server->list;
    tmp->client != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->client->socket, &server->readfds))
            recv_command(tmp->client, server);
        if (tmp->next == NULL || tmp->client == NULL)
            break;
    }
}

static void set_all_in_fd(server_t *server, int *max_fd)
{
    FD_SET(server->socket, &server->readfds);
    FD_SET(server->socket, &server->writefds);
    *max_fd = server->socket;
    for (client_list_t *tmp = server->list;
    tmp->client != NULL; tmp = tmp->next) {
        if (tmp->client == NULL)
            break;
        FD_SET(tmp->client->socket, &server->readfds);
        FD_SET(tmp->client->socket, &server->writefds);
        if (tmp->client->socket > *max_fd)
            *max_fd = tmp->client->socket;
        if (tmp->next == NULL)
            break;
    }
}

//debug
static void print_all_map(server_t *server)
{
    for (int i = 0; i < server->info_game.width; i++) {
        for (int j = 0; j < server->info_game.height; j++) {
            if (server->game->map[i][j].drone_list == NULL)
                continue;
            printf("Tile %d %d\n", i, j);
            for (linked_list_drone_t *tmp = server->game->map[i][j].drone_list;
            tmp != NULL; tmp = tmp->next) {
                printf("Drone %d %d %d %d %d %s\n", tmp->drone->id,
                    tmp->drone->level, tmp->drone->x, tmp->drone->y,
                    tmp->drone->orientation, tmp->drone->team_name);
            }
        }
    }
}

int server_loop(server_t *server)
{
    int max_fd = server->socket;
    int select_status;
    struct timeval timeout = {0, 0};
    server->list = create_client_list();
    while (1) {
        if (FD_ISSET(server->socket, &server->readfds))
            new_client(server);
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        set_all_in_fd(server, &max_fd);
        select_status = select(
            max_fd + 1, &server->readfds, NULL, NULL, &timeout);
        if (!check_return_value(select_status, SELECT))
            continue;
        client_already_connected(server);
        print_all_map(server);
        sleep(2);
    }
}
// at each loop, if time is up, do one game tick: TODO
