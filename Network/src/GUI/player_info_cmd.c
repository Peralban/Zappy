/*
** EPITECH PROJECT, 2024
** player_info_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

static client_list_t *get_drone_by_id(server_t *server, int id, int cli_socket)
{
    client_list_t *tmp = server->list;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->client->drone == NULL)
            continue;
        if (tmp->client->drone->id == id)
            return tmp;
    }
    send(cli_socket, "ko\n", 3, 0);
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
    char *response = calloc(1024, sizeof(char));
    char orientation[4] = {'N', 'E', 'S', 'W'};
    int ref_id = atoi(args[0]);
    client_list_t *tmp = NULL;

    if (ref_id < 0 || !is_number(args[0])) {
        send(client->socket, "ko, invalid id\n", 15, 0);
        return;
    }
    tmp = get_drone_by_id(server, ref_id, client->socket);
    if (tmp == NULL)
        return;
    sprintf(response, "ppo %d %d %d %c\n", ref_id,
    tmp->client->drone->x, tmp->client->drone->y,
    orientation[tmp->client->drone->orientation]);
    send(client->socket, response, strlen(response), 0);
    free(response);
}

void get_player_level(client_t *client, server_t *server, char **args)
{
    char *response = calloc(1024, sizeof(char));
    int ref_id = atoi(args[0]);
    client_list_t *tmp = NULL;

    if (ref_id < 0 || !is_number(args[0])) {
        send(client->socket, "ko, invalid id\n", 15, 0);
        return;
    }
    tmp = get_drone_by_id(server, ref_id, client->socket);
    if (tmp == NULL)
        return;
    sprintf(response, "plv %d %d\n", ref_id, tmp->client->drone->level);
    send(client->socket, response, strlen(response), 0);
    free(response);
}

void get_player_inventory(client_t *client, server_t *server, char **args)
{
    char *response = calloc(1024, sizeof(char));
    int ref_id = atoi(args[0]);
    client_list_t *tmp = NULL;

    if (ref_id < 0 || !is_number(args[0])) {
        send(client->socket, "ko, invalid id\n", 15, 0);
        return;
    }
    tmp = get_drone_by_id(server, ref_id, client->socket);
    if (tmp == NULL)
        return;
    tmp->client->drone->inventory[0] = 0;
    sprintf(response, "pin %d %d %d %d %d %d %d %d %d %d\n", ref_id,
    tmp->client->drone->x, tmp->client->drone->y,
    tmp->client->drone->inventory[0], tmp->client->drone->inventory[1],
    tmp->client->drone->inventory[2], tmp->client->drone->inventory[3],
    tmp->client->drone->inventory[4], tmp->client->drone->inventory[5],
    tmp->client->drone->inventory[6]);
    send(client->socket, response, strlen(response), 0);
    free(response);
}
