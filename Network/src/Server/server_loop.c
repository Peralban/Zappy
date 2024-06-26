/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server_loop.c
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include "Game/game_functions.h"
#include "GuiProtocol/gui.h"
#include "GuiProtocol/gui_event.h"
#include "Admin/admin.h"
#include "lib/my.h"
#include <stdio.h>

static void start_playing_client(client_t *client, server_t *server,
    char *buffer, int i)
{
    server->game->teams[i].nb_egg--;
    sprintf(buffer, "%d\n%d %d\n",
        server->game->teams[i].nb_egg,
        server->info_game.width, server->info_game.height);
    send(client->socket, buffer, strlen(buffer), 0);
    client->state = PLAYING;
    create_player(server, client, server->info_game.team_names[i]);
    gui_pnw(server, client->drone);
}

static int start_communication_with_client(client_t *client,
    server_t *server, char *buffer)
{
    if (strcmp(buffer, "GRAPHIC") == 0 || strcmp(buffer, "ADMIN") == 0) {
        client->state = buffer[0] == 'G' ? GRAPHIC : ADMIN;
        start_gui_client(server, client);
        return 0;
    }
    for (int i = 0; server->info_game.team_names[i] != NULL; i++) {
        if (strcmp(buffer, server->info_game.team_names[i]) == 0 &&
            server->game->teams[i].nb_egg > 0) {
            start_playing_client(client, server, buffer, i);
            return 0;
        }
    }
    if (send(client->socket, "ko\n", 3, 0) < 0) {
        eject_client_from_server(client, server);
        return 1;
    }
    return 0;
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

static void exec_one_gui_command(client_t *client, server_t *server,
    char *command)
{
    char **command_args = my_str_to_word_array(command, " ");
    int len = my_array_len(command_args);

    for (int j = 0; commands_gui[j].name != NULL; j++) {
        if (strcmp(command_args[0], commands_gui[j].name) != 0)
            continue;
        if (len == 1 + commands_gui[j].nb_args)
            commands_gui[j].function(client, server, command_args + 1);
        else
            gui_sbp(client->socket);
        my_free_array(command_args);
        return;
    }
    gui_suc(client->socket);
    my_free_array(command_args);
}

static void exec_gui_commands(client_t *client, server_t *server, char *buffer)
{
    char **commands_arr = my_str_to_word_array(buffer, "\n");

    for (int i = 0; commands_arr[i] != NULL; i++)
        exec_one_gui_command(client, server, commands_arr[i]);
    my_free_array(commands_arr);
}

static int client_state_switch(client_t *client, server_t *server,
    char *buffer)
{
    switch (client->state) {
        case WAITING:
            return start_communication_with_client(client, server, buffer);
        case PLAYING:
            push_command(client, buffer);
            break;
        case GRAPHIC:
            exec_gui_commands(client, server, buffer);
            break;
        case ADMIN:
            exec_admin_commands(client, server, buffer);
            break;
    }
    return 0;
}

static int recv_command(client_t *client, server_t *server)
{
    char buffer[1024];
    int buffer_length;

    buffer_length = (int)recv(client->socket, buffer, 1024, 0);
    if (!check_return_value(buffer_length, RECV))
        return 0;
    if (buffer[buffer_length - 2] == '\r')
        buffer[buffer_length - 2] = '\0';
    else
        buffer[buffer_length - 1] = '\0';
    if (strlen(buffer) == 0)
        strcpy(buffer, "quit");
    if (strcmp(buffer, "quit") == 0) {
        reset_client(client, server);
        eject_client_from_server(client, server);
        client_already_connected(server);
        return 1;
    } else
        return client_state_switch(client, server, buffer);
}

void client_already_connected(server_t *server)
{
    for (client_list_t *tmp = server->list;
    tmp->client != NULL; tmp = tmp->next) {
        if (FD_ISSET(tmp->client->socket, &server->readfds) &&
        recv_command(tmp->client, server)) {
            client_already_connected(server);
            break;
        }
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

int server_loop(server_t *server)
{
    int max_fd = server->socket;
    int status;
    struct timeval timeout = {0, 0};

    while (!replace_stop(-1)) {
        if (FD_ISSET(server->socket, &server->readfds))
            new_client(server);
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        set_all_in_fd(server, &max_fd);
        status = select(max_fd + 1, &server->readfds, NULL, NULL, &timeout);
        if (!check_return_value(status, SELECT))
            continue;
        client_already_connected(server);
        game_tick(server);
    }
    gui_smg(server, "Server shutting down");
    gui_seg(server);
    return end_server(server);
}
