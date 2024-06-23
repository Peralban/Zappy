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
#include "GuiProtocol/gui_event.h"

static void exec_command(char *command, client_t *client, server_t *server)
{
    char **command_args = my_str_to_word_array(command, " ");
    int len = word_nbr(command, " ");

    if (command_args == NULL)
        return;
    for (int i = 0; commands_opt[i].name != NULL; i++) {
        if (strcmp(command_args[0], "Broadcast") == 0) {
            broadcast(client, server, (char *[2]){command + 10, NULL});
            return my_free_array(command_args);
        }
        if (strcmp(command_args[0], commands_opt[i].name) == 0 &&
        len == 1 + commands_opt[i].nb_args) {
            commands_opt[i].function(client, server, command_args + 1);
            my_free_array(command_args);
            return;
        }
    }
    my_free_array(command_args);
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
    int len = word_nbr(client->command[0], " ");
    char **command_args = NULL;

    if (client->command[0] == NULL)
        return;
    command_args = my_str_to_word_array(client->command[0], " ");
    for (int i = 0; commands_opt[i].name != NULL; i++) {
        if (command_args[0] == NULL)
            return;
        if (strcmp(command_args[0], "Broadcast") == 0) {
            client->drone->ticks = 6;
            return my_free_array(command_args);
        }
        if (strcmp(command_args[0], commands_opt[i].name) == 0 &&
        len == 1 + commands_opt[i].nb_args) {
            client->drone->ticks = commands_opt[i].duration - 1;
            return my_free_array(command_args);
        }
    }
    my_free_array(command_args);
}

static bool update_life(client_t *client, server_t *server)
{
    drone_t *drone = client->drone;

    if (drone->life_ticks == 0) {
        if (drone->inventory[FOOD] > 0) {
            drone->life_ticks = 126;
            (drone->inventory[FOOD])--;
        } else {
            send(client->socket, "dead\n", 5, 0);
            gui_pdi(server, drone->id);
            reset_client(client, server);
            return false;
        }
    } else
        drone->life_ticks--;
    return true;
}

static bool check_conditions(char *command, client_t *client, server_t *server)
{
    bool (*condition)(client_t *client, server_t *server, char **args) = NULL;

    for (int i = 0; commands_opt[i].name != NULL; i++)
        if (strcmp(command, commands_opt[i].name) == 0)
            condition = commands_opt[i].condition;
    if (condition == NULL)
        return true;
    return condition(client, server, NULL);
} //the NULL is supposed to be args, but it is not used in the function atm.

static void update_incantation_master(drone_t *drone, server_t *server,
    int lvl)
{
    if (drone->level == lvl && drone->incantation_master) {
        drone->incantation_master = false;
        incantation(get_client_by_drone_id(drone->id, server), server, NULL);
        shift_commands(get_client_by_drone_id(drone->id, server));
    }
}

static void update_incantation_tile(int x, int y, int lvl, server_t *server)
{
    char buffer[1024];

    sprintf(buffer, "Current level: %d\n", lvl + 1);
    for (linked_list_drone_t *tmp = server->game->map[x][y].drone_list;
    tmp != NULL; tmp = tmp->next) {
        update_incantation_master(tmp->drone, server, lvl);
        if (tmp->drone->level == lvl) {
            tmp->drone->level++;
            tmp->drone->incantation_ticks = 0;
            send(get_client_by_drone_id(tmp->drone->id, server)->socket,
                buffer, strlen(buffer), 0);
            gui_pie(server, tmp->drone);
        }
    }
    for (int i = 1; i < 7; i++) {
        server->game->map[x][y].inventory[i] -=
                incantation_level_prerequisites[lvl - 1][i];
        server->game->picked_up_items[i] +=
                incantation_level_prerequisites[lvl - 1][i];
    }
}

static bool update_incantation(client_t *client, server_t *server)
{
    if (client->drone->incantation_ticks == 0)
        return false;
    client->drone->incantation_ticks--;
    if (client->drone->incantation_ticks == 0) {
        if (check_incantation_prerequisites(client, server)) {
            update_incantation_tile(client->drone->x, client->drone->y,
                client->drone->level, server);
        } else {
            send(client->socket, "ko\n", 3, 0);
            gui_pie(server, client->drone);
        }
    }
    return true;
}

static void update_drone_action(client_t *client, server_t *server)
{
    if (client->drone->ticks == 0) {
        exec_command(client->command[0], client, server);
        shift_commands(client);
    }
    client->drone->ticks--;
}

void update_players(server_t *server)
{
    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp->client == NULL || tmp->client->drone == NULL
        || tmp->client->state != PLAYING)
            continue;
        if (!update_life(tmp->client, server))
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
