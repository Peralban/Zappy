/*
** EPITECH PROJECT, 2024
** admin_function.c
** File description:
** DESCRIPTION
*/

#include "Admin/admin.h"

static bool is_nbr(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

static void change_level(client_t *client, int new_level, client_t *admin)
{
    char client_resp[1024] = {0};
    int current_level = client->drone->level;

    if (new_level < 0 || new_level > 8)
        return print_and_send(current_level + new_level < 0 ?
        "Drone level can't be negative\n" :
        "Drone level can't be higher than 8\n", admin);
    if (current_level == new_level || new_level == 0) {
        sprintf(client_resp, "Drone %d level is already %d\n",
        client->drone->id, new_level);
        return print_and_send(client_resp, admin);
    }
    client->drone->level = new_level;
    sprintf(client_resp, "Your current has been changed by an admin to %d\n",
    new_level);
    send(client->socket, client_resp, strlen(client_resp), 0);
    sprintf(client_resp, "Drone %d level has been changed to %d\n",
    client->drone->id, new_level);
    print_and_send(client_resp, admin);
}

void adm_level_up(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    int ref_id = atoi(args[0]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!is_nbr(args[0]))
        return print_and_send("Level must be a number\n", client);
    if (tmp == NULL)
        return print_and_send("Drone with id %d not found\n", client);
    change_level(tmp->client, tmp->client->drone->level + 1, client);
}

void adm_level_down(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    int ref_id = atoi(args[0]);
    char rep[1024] = {0};
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!is_nbr(args[0]))
        return print_and_send("Level must be a number\n", client);
    if (tmp == NULL) {
        sprintf(rep, "Drone with id %d not found\n", ref_id);
        return print_and_send(rep, client);
    }
    change_level(tmp->client, tmp->client->drone->level - 1, client);
}

void adm_set_level(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    bool nbr[2] = {is_nbr(args[0]), is_nbr(args[1])};
    int ref_id = atoi(args[0]);
    int new_level = atoi(args[1]);
    char rep[1024] = {0};
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!nbr[0] || !nbr[1])
        return print_and_send("Level must be a number\n", client);
    if (tmp == NULL) {
        sprintf(rep, "Drone with id %d not found\n", ref_id);
        return print_and_send(rep, client);
    }
    change_level(tmp->client, new_level, client);
}

static linked_list_drone_t *get_last_node(linked_list_drone_t *list)
{
    linked_list_drone_t *tmp = list;

    if (tmp == NULL)
        return NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    return tmp;
}

static void add_drone_at(in_game_t *game, drone_t *drone, int x, int y)
{
    tile_t *tile = &game->map[x][y];
    linked_list_drone_t *tmp = get_last_node(tile->drone_list);

    if (tmp == NULL) {
        tile->drone_list = calloc(1, sizeof(linked_list_drone_t));
        if (tile->drone_list == NULL)
            return;
        tile->drone_list->drone = drone;
        return;
    }
    tmp->next = calloc(1, sizeof(linked_list_drone_t));
    if (tmp->next == NULL)
        return;
    tmp->next->prev = tmp;
    tmp->next->drone = drone;
}

static void tell_new_coord(client_t *client)
{
    char buffer[1024] = {0};

    sprintf(buffer, "You have been teleported to (%d, %d)\n",
    client->drone->x, client->drone->y);
    send(client->socket, buffer, strlen(buffer), 0);
}

void adm_tp(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    int coord[2] = {atoi(args[1]), atoi(args[2])};
    client_list_t *tmp = get_drone_by_id(server, atoi(args[0]));

    if (!is_nbr(args[0]) || !is_nbr(args[0]) || !is_nbr(args[0]))
        return print_and_send("ID or Coordinates must be numbers\n", client);
    if (coord[0] < 0 || coord[0] >= server->info_game.width || coord[1] < 0 ||
    coord[1] >= server->info_game.height)
        return print_and_send("Coordinates out of map\n", client);
    if (tmp == NULL)
        return print_and_send("Drone with this id not found\n", client);
    remove_drone_in_list(&server->game->map[tmp->client->drone->x]
    [tmp->client->drone->y].drone_list, tmp->client->drone);
    tmp->client->drone->x = coord[0];
    tmp->client->drone->y = coord[1];
    add_drone_at(server->game, tmp->client->drone, coord[0], coord[1]);
    print_and_send("Drone has been teleported\n", client);
    tell_new_coord(tmp->client);
}

void adm_set_inventory(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    bool nbr[8] = {is_nbr(args[0]), is_nbr(args[1]),
    is_nbr(args[2]), is_nbr(args[3]), is_nbr(args[4]),
    is_nbr(args[5]), is_nbr(args[6]), is_nbr(args[7])};
    int ref_id = atoi(args[0]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!nbr[0] || !nbr[1] || !nbr[2] || !nbr[3] || !nbr[4] || !nbr[5] ||
    !nbr[6] || !nbr[7])
        return print_and_send("Inventory must have numbers\n", client);
    if (tmp == NULL)
        return print_and_send("Drone with this id not found\n", client);
    for (int i = 1; i < 8; i++)
        tmp->client->drone->inventory[i - 1] = atoi(args[i]);
    print_and_send("Inventory has been changed\n", client);
}
