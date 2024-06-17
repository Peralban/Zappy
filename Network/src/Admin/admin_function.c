/*
** EPITECH PROJECT, 2024
** admin_function.c
** File description:
** DESCRIPTION
*/

#include "Admin/admin.h"

static bool is_a_number(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

static client_list_t *get_drone_by_id(server_t *server, int id)
{
    client_list_t *tmp = server->list;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->client->drone == NULL)
            continue;
        if (tmp->client->drone->id == id)
            return tmp;
    }
    return NULL;
}

static void change_level(client_t *client, int new_level)
{
    char client_resp[1024] = {0};
    int current_level = client->drone->level;

    if (new_level < 0 || new_level > 8) {
        printf(current_level + new_level < 0 ?
        "Drone level can't be negative\n" :
        "Drone level can't be higher than 8\n");
        return;
    }
    if (current_level == new_level || new_level == 0) {
        printf("Drone level is already %d\n", current_level);
        return;
    }
    client->drone->level = new_level;
    sprintf(client_resp, "Your current has been changed by an admin to %d\n",
    new_level);
    send(client->socket, client_resp, strlen(client_resp), 0);
    printf("Drone %d level changed from %d to %d\n", client->drone->id,
    current_level, new_level);
}

void adm_level_up(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    int ref_id = atoi(args[0]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!is_a_number(args[0])) {
        printf("Level must be a number\n");
        return;
    }
    if (tmp == NULL) {
        printf("Drone with id %d not found\n", ref_id);
        return;
    }
    change_level(tmp->client, tmp->client->drone->level + 1);
}

void adm_level_down(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    int ref_id = atoi(args[0]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!is_a_number(args[0])) {
        printf("Level must be a number\n");
        return;
    }
    if (tmp == NULL) {
        printf("Drone with id %d not found\n", ref_id);
        return;
    }
    change_level(tmp->client, tmp->client->drone->level - 1);
}

void adm_set_level(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    bool nbr[2] = {is_a_number(args[0]), is_a_number(args[1])};
    int ref_id = atoi(args[0]);
    int new_level = atoi(args[1]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!nbr[0] || !nbr[1]) {
        printf((!nbr[0] ? "Ref id must be a number\n" :
        "Level must be a number\n"));
        return;
    }
    if (tmp == NULL) {
        printf("Drone with id %d not found\n", ref_id);
        return;
    }
    change_level(tmp->client, new_level);
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

void adm_tp(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    bool nbr[3] = {
    is_a_number(args[0]), is_a_number(args[1]), is_a_number(args[2])};
    int coord[2] = {atoi(args[1]), atoi(args[2])};
    char *return_msg[4] = { "Ref id must be a number\n", "X must be a number\n"
    , "Y must be a number\n", ""};
    client_list_t *tmp = get_drone_by_id(server, atoi(args[0]));

    if (!nbr[0] || !nbr[1] || !nbr[2]) {
        for (int i = 0; i < 3; i++)
            printf((!nbr[i] ? return_msg[i] : return_msg[3]));
        return;
    }
    if (tmp == NULL)
        return (void) printf("Drone with id %d not found\n", atoi(args[0]));
    remove_drone_in_list(&server->game->map[tmp->client->drone->x]
    [tmp->client->drone->y].drone_list, tmp->client->drone);
    tmp->client->drone->x = coord[0];
    tmp->client->drone->y = coord[1];
    add_drone_at(server->game, tmp->client->drone, coord[0], coord[1]);
}

void adm_set_inventory(__attribute__((unused))
    client_t *client, server_t *server, char **args)
{
    bool nbr[8] = {is_a_number(args[0]), is_a_number(args[1]),
    is_a_number(args[2]), is_a_number(args[3]), is_a_number(args[4]),
    is_a_number(args[5]), is_a_number(args[6]), is_a_number(args[7])};
    int ref_id = atoi(args[0]);
    char *item[8] = {"", "food", "linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame"};
    client_list_t *tmp = get_drone_by_id(server, ref_id);

    if (!nbr[0] || !nbr[1] || !nbr[2] || !nbr[3] || !nbr[4] || !nbr[5] ||
    !nbr[6] || !nbr[7]) {
        for (int i = 0; i < 8; i++)
            printf((!nbr[i] ? "item %s must be a number\n" : ""), item[i]);
        return;
    }
    if (tmp == NULL) {
        printf("Drone with id %d not found\n", ref_id);
        return;
    }
    for (int i = 1; i < 8; i++)
        tmp->client->drone->inventory[i - 1] = atoi(args[i]);
}
