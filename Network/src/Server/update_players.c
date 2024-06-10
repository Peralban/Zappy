/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Server/server.h"
#include "Game/game.h"
#include "Game/game_command.h"
#include "lib/my.h"


static void exec_command(char *command, client_t *client, server_t *server)
{
    char **command_array = my_str_to_word_array(command, " \n");
    int len = word_nbr(command, " \n");

    if (command_array == NULL)
        return;
    for (int i = 0; commands_opt[i].name != NULL; i++) {
        if (strcmp(command_array[0], commands_opt[i].name) == 0 &&
        len == 1 + commands_opt[i].nb_args) {
            commands_opt[i].function(client, server, command_array[1]);
            my_free_array(command_array);
            return;
        }
    }
    my_free_array(command_array);
    send(client->socket, "ko\n", 3, 0);
}

static void shift_commands(client_t *client)
{
    free(client->command[0]);
    for (int i = 0; i < MAX_COMMAND - 1; i++) {
        client->command[i] = client->command[i + 1];
    }
    client->command[MAX_COMMAND - 1] = NULL;
    set_ticks(client);
    client->drone->condition = false;
}

void set_ticks(client_t *client)
{
    int len = word_nbr(client->command[0], " \n");

    for (int i = 0; commands_opt[i].name != NULL; i++) {
        if (client->command[0] == NULL)
            return;
        if (strcmp(client->command[0], commands_opt[i].name) == 0 &&
        len == 1 + commands_opt[i].nb_args) {
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

static bool update_life(client_t *client)
{
    drone_t *drone = client->drone;

    if (drone->life_ticks == 0) {
        if (drone->inventory[FOOD] > 0) {
            drone->life_ticks = 126;
            drone->inventory[FOOD]--;
        } else {
            send(client->socket, "dead\n", 5, 0);
            reset_client(client);
            return false;
        }
    } else
        drone->life_ticks--;
    return true;
}

static bool check_conditions(char *command, client_t *client, server_t *server)
{
    bool (*condition)(client_t *client, server_t *server, char *args) = NULL;

    for (int i = 0; commands_opt[i].name != NULL; i++)
        if (strcmp(command, commands_opt[i].name) == 0)
            condition = commands_opt[i].condition;
    if (condition == NULL)
        return true;
    return condition(client, server, NULL);
} //the NULL is supposed to be args, but it is not used in the function atm.

static void update_incantation_tile(int x, int y, int lvl, server_t *server)
{
    char buffer[1024];

    sprintf(buffer, "Current level: %d\n", lvl + 1);
    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp->client->drone->x == x && tmp->client->drone->y == y &&
        tmp->client->drone->level == lvl) {
            tmp->client->drone->level++;
            tmp->client->drone->incantation_ticks = 0;
            send(tmp->client->socket, buffer, strlen(buffer), 0);
        }
    }
    for (int i = 1; i < 7; i++)
        server->game->map[x][y].inventory[i] -=
            incantation_level_prerequisites[lvl - 1][i];
}

static bool update_incantation(client_t *client, server_t *server)
{
    char buffer[1024];

    if (client->drone->incantation_ticks == 0)
        return false;
    client->drone->incantation_ticks--;
    if (client->drone->incantation_ticks == 0) {
        if (check_incantation_prerequisites(client, server)) {
            update_incantation_tile(client->drone->x, client->drone->y,
                client->drone->level, server);
        } else {
            sprintf(buffer, "Current level: %d\n", client->drone->level);
            send(client->socket, buffer, strlen(buffer), 0);
        }
    }
    return true;
}

static void update_drone_action(client_t *client, server_t *server)
{
    if (client->drone->ticks == 0) {
        exec_command(client->command[0], client, server);
        shift_commands(client);
    } else
        client->drone->ticks--;
}

void update_players(server_t *server)
{
    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp->client == NULL || tmp->client->drone == NULL)
            continue;
        if (!update_life(tmp->client))
            continue;
        if (update_incantation(tmp->client, server))
            continue;
        if (tmp->client->command[0] == NULL)
            continue;
        if (!tmp->client->drone->condition &&
        !check_conditions(tmp->client->command[0], tmp->client, server)) {
            shift_commands(tmp->client);
            continue;
        } else
            tmp->client->drone->condition = true;
        update_drone_action(tmp->client, server);
    }
}
