/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_loop.c
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include "Game/game_functions.h"
#include "Game/game_command.h"
#include "Game/game.h"
#include "lib/my.h"
#include <stdio.h>
#include <sys/time.h>

static void start_communication_with_client(client_t *client,
    server_t *server, char *buffer)
{
    for (int i = 0; server->info_game.team_names[i] != NULL; i++) {
        if (strcmp(buffer, "GRAPHIC") == 0) {
            client->state = GRAPHIC;
            return;
        }
        if (strcmp(buffer, server->info_game.team_names[i]) == 0 &&
            server->game->teams[i].nb_egg > 0) {
            server->game->teams[i].nb_egg--;
            sprintf(buffer, "%d\n%d %d\n",
                server->game->teams[i].nb_egg,
                server->info_game.width, server->info_game.height);
            send(client->socket, buffer, strlen(buffer), 0);
            client->state = PLAYING;
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

static void push_command(client_t *client, char *buffer)
{
    char **commands_arr = my_str_to_word_array(buffer, "\n");
    int j;

    for (int i = 0; commands_arr[i] != NULL; i++) {
        if (client->command[0] == NULL) {
            client->command[0] = strdup(commands_arr[i]);
            set_ticks(client);
            continue;
        }
        for (j = 0; j != MAX_COMMAND && client->command[j] != NULL; j++);
        if (j < MAX_COMMAND)
            client->command[j] = strdup(commands_arr[i]);
    }
    my_free_array(commands_arr);
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
    if (client->state == WAITING)
        start_communication_with_client(client, server, buffer);
    if (client->state == PLAYING)
        push_command(client, buffer);
    if (client->state == GRAPHIC)
        return;
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

uint64_t get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}

static void spawn_resources(server_t *server)
{
    int x;
    int y;

    for (int k = 0; k < MAX_ITEMS; k++) {
        for (int i = 0; i < server->game->picked_up_items[k] &&
        server->game->picked_up_items[k] > 0; i++) {
            x = rand() % server->info_game.width;
            y = rand() % server->info_game.height;
            server->game->map[x][y].inventory[k]++;
        }
        if (server->game->picked_up_items[k] > 0) {
            server->game->picked_up_items[k] = 0;
        }
    }
}

static void game_tick(server_t *server)
{
    static uint64_t last_tick_time = 0;
    uint64_t current_time = get_time();

    if (current_time - last_tick_time >=
    (1000000 / (uint64_t)server->info_game.freq)) {
        update_players(server);
        server->game->spawn_tick++;
        last_tick_time = current_time;
    }
    if (server->game->spawn_tick >= 20) {
        server->game->spawn_tick = 0;
        spawn_resources(server);
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
        game_tick(server);
    }
}
