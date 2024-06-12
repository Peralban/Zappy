/*
** EPITECH PROJECT, 2024
** player_info_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

linked_list_drone_t *get_drone_by_id(server_t *server, int id, int cli_socket)
{
    linked_list_drone_t *tmp = server->list;

    for (; tmp != NULL; tmp = tmp->next)
        if (tmp->drone->id == id)
            return tmp;
    send(cli_socket, "ko\n", 3, 0);
    return NULL;
}

void get_player_position(server_t *server, client_t *client, char **args)
{
    char *response = calloc(1024, sizeof(char));
    char orientation[4] = {'N', 'E', 'S', 'W'};
    int ref_id = atoi(args[1]);
    linked_list_drone_t *tmp = get_drone_by_id(server, ref_id);

    if (tmp == NULL)
        return;
    sprintf(response, "ppo #%d %d %d %c\n", ref_id,
    tmp->drone->x, tmp->drone->y, orientation[tmp->drone->orientation]);
    send(client->socket, response, strlen(response), 0);
    free(response);
}

void get_player_level(server_t *server, client_t *client, char **args)
{
    char *response = calloc(1024, sizeof(char));
    int ref_id = atoi(args[1]);
    linked_list_drone_t *tmp = get_drone_by_id(server, ref_id);

    if (tmp == NULL)
        return;
    sprintf(response, "plv #%d %d\n", ref_id, tmp->drone->level);
    send(client->socket, response, strlen(response), 0);
    free(response);
}

void get_player_inventory(server_t *server, client_t *client, char **args)
{
    char *response = calloc(1024, sizeof(char));
    int ref_id = atoi(args[1]);
    linked_list_drone_t *tmp = get_drone_by_id(server, ref_id);

    if (tmp == NULL)
        return;
    sprintf(response, "pin #%d %d %d %d %d %d %d %d %d %d\n", ref_id,
    tmp->drone->x, tmp->drone->y,
    tmp->drone->inventory[0], tmp->drone->inventory[1],
    tmp->drone->inventory[2], tmp->drone->inventory[3],
    tmp->drone->inventory[4], tmp->drone->inventory[5],
    tmp->drone->inventory[6]);
    send(client->socket, response, strlen(response), 0);
    free(response);
}
