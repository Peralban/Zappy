/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Server/server.h"
#include "Game/game.h"
#include "Game/game_command.h"


static void exec_command(char *command, client_t *client, server_t *server)
{
    for (int i = 0; commands_opt[i].name != NULL; i++) {
        if (strcmp(command, commands_opt[i].name) == 0) {
            commands_opt[i].function(client, server);
            return;
        }
    }
    send(client->socket, "ko\n", 3, 0);
}

static void shift_commands(char **commands)
{
    free(commands[0]);
    for (int i = 0; i < MAX_COMMAND - 1; i++) {
        commands[i] = commands[i + 1];
    }
    commands[MAX_COMMAND - 1] = NULL;
}

void set_ticks(client_t *client)
{
    for (int i = 0; commands_opt[i].name != NULL; i++) {
        if (client->command[0] == NULL)
            return;
        if (strcmp(client->command[0], commands_opt[i].name) == 0) {
            client->drone->ticks = commands_opt[i].duration;
            return;
        }
    }
}

static void reset_client(client_t *client)
{
    free(client->drone);
    client->drone = NULL;
    for (int i = 0; i < MAX_COMMAND; i++) {
        free(client->command[i]);
        client->command[i] = NULL;
    }
    client->state = WAITING;
}

static void update_life(client_t *client)
{
    drone_t *drone = client->drone;

    if (drone->life_ticks == 0) {
        if (drone->inventory[FOOD] > 0) {
            drone->life_ticks = 126;
            drone->inventory[FOOD]--;
        } else {
            send(client->socket, "dead\n", 5, 0);
            reset_client(client);
        }
    } else
        drone->life_ticks--;
}

void update_players(server_t *server)
{
    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp->client == NULL || tmp->client->drone == NULL)
            continue;
        update_life(tmp->client);
        if (tmp->client->command[0] == NULL)
            continue;
        if (tmp->client->drone->ticks == 0) {
            exec_command(tmp->client->command[0], tmp->client, server);
            shift_commands(tmp->client->command);
            set_ticks(tmp->client);
        } else
            tmp->client->drone->ticks--;
    }
}
