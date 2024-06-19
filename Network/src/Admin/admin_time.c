/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Admin/admin.h"

void adm_pause(client_t *client, server_t *server, char **args)
{
    (void)args;
    (void)client;
    server->game->paused = !server->game->paused;
    if (server->game->paused) {
        printf("Game paused\n");
        send(client->socket, "Game paused\n", 12, 0);
    } else {
        printf("Game unpaused\n");
        send(client->socket, "Game unpaused\n", 14, 0);
    }
}

static bool is_number(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

void adm_set_freq(client_t *client, server_t *server, char **args)
{
    if (!is_number(args[0])) {
        send(client->socket, "Invalid frequency\n", 19, 0);
        return;
    }
    server->info_game.freq = atoi(args[0]);
    printf("Frequency set to %d\n", server->info_game.freq);
    send(client->socket, "Frequency set\n", 14, 0);
}

void adm_tick(client_t *client, server_t *server, char **args)
{
    int nb = atoi(args[0]);
    tick_command_admin_t data;

    for (int i = 0; tick_commands_admin[i].type != 0; i++)
        if (tick_commands_admin[i].type == args[1][0]) {
            data = tick_commands_admin[i];
            break;
        }
    if (is_number(args[0]) == false || data.type_str == NULL) {
        send(client->socket, "Invalid tick\n", 13, 0);
        return;
    }
    if (data.multiplier != 0)
        nb = nb * data.multiplier * server->info_game.freq;
    printf("Simulate %s %s\n", args[0], data.type_str);
    send(client->socket, "Simulating tick\n", 16, 0);
    for (int i = 0; i < nb; i++)
        game_tick_action(server);
    printf("Tick done\n");
    send(client->socket, "Tick done\n", 10, 0);
}
