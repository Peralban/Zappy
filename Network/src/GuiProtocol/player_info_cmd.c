/*
** EPITECH PROJECT, 2024
** player_info_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"
#include "GuiProtocol/gui_event.h"

static client_list_t *get_drone_by_id(server_t *server, int id, int cli_socket)
{
    client_list_t *tmp = server->list;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->client->drone == NULL)
            continue;
        if (tmp->client->drone->id == id)
            return tmp;
    }
    gui_sbp(cli_socket);
    return NULL;
}

static bool is_number(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

void get_player_position(client_t *client, server_t *server, char **args)
{
    char response[1024] = {0};
    char orientation[4] = {'N', 'E', 'S', 'W'};
    int ref_id = atoi(args[0]);
    client_list_t *tmp = NULL;

    if (ref_id < 0 || !is_number(args[0])) {
        gui_sbp(client->socket);
        return;
    }
    tmp = get_drone_by_id(server, ref_id, client->socket);
    if (tmp == NULL)
        return;
    sprintf(response, "ppo %d %d %d %c\n", ref_id,
    tmp->client->drone->x, tmp->client->drone->y,
    orientation[tmp->client->drone->orientation]);
    send(client->socket, response, strlen(response), 0);
}

void get_player_level(client_t *client, server_t *server, char **args)
{
    char response[1024] = {0};
    int ref_id = atoi(args[0]);
    client_list_t *tmp = NULL;

    if (ref_id < 0 || !is_number(args[0])) {
        gui_sbp(client->socket);
        return;
    }
    tmp = get_drone_by_id(server, ref_id, client->socket);
    if (tmp == NULL)
        return;
    sprintf(response, "plv %d %d\n", ref_id, tmp->client->drone->level);
    send(client->socket, response, strlen(response), 0);
}

void get_player_inventory(client_t *client, server_t *server, char **args)
{
    char response[1024] = {0};
    int ref_id = atoi(args[0]);
    client_list_t *tmp = NULL;

    if (ref_id < 0 || !is_number(args[0])) {
        gui_sbp(client->socket);
        return;
    }
    tmp = get_drone_by_id(server, ref_id, client->socket);
    if (tmp == NULL)
        return;
    sprintf(response, "pin %d %d %d %d %d %d %d %d %d %d\n", ref_id,
    tmp->client->drone->x, tmp->client->drone->y,
    tmp->client->drone->inventory[0], tmp->client->drone->inventory[1],
    tmp->client->drone->inventory[2], tmp->client->drone->inventory[3],
    tmp->client->drone->inventory[4], tmp->client->drone->inventory[5],
    tmp->client->drone->inventory[6]);
    send(client->socket, response, strlen(response), 0);
}
