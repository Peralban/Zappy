/*
** EPITECH PROJECT, 2024
** admin_function_bis.c
** File description:
** DESCRIPTION
*/

#include "Admin/admin.h"

client_list_t *get_drone_by_id(server_t *server, int id)
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

void print_and_send(char *msg, client_t *client)
{
    send(client->socket, msg, strlen(msg), 0);
    printf("%s\n", msg);
}

void adm_locate(client_t *client, server_t *server, char **args)
{
    int ref_id = atoi(args[0]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);
    char buffer[1024] = {0};

    if (tmp == NULL)
        return print_and_send("Drone not found\n", client);
    sprintf(buffer, "Drone %d is at (%d, %d)\n", ref_id,
    tmp->client->drone->x, tmp->client->drone->y);
    print_and_send(buffer, client);
}

void adm_get_inventory(client_t *client, server_t *server, char **args)
{
    int ref_id = atoi(args[0]);
    client_list_t *tmp = get_drone_by_id(server, ref_id);
    char buffer[1024] = {0};

    if (tmp == NULL)
        return print_and_send("Drone not found\n", client);
    sprintf(buffer, "Drone %d inventory:\n\t"
    "Food: %d\n\tLinemate: %d\n\tDeraumere: %d\n\tSibur: %d\n\tMendiane: %d\n"
    "\tPhiras: %d\n\tThystame: %d\n", ref_id, tmp->client->drone->inventory[0],
    tmp->client->drone->inventory[1], tmp->client->drone->inventory[2],
    tmp->client->drone->inventory[3], tmp->client->drone->inventory[4],
    tmp->client->drone->inventory[5], tmp->client->drone->inventory[6]);
    print_and_send(buffer, client);
}

void adm_help(client_t *client, server_t *server, char **args)
{
    char buffer[1024] = {0};

    (void)server;
    (void)args;
    sprintf(buffer, "Available commands:\n"
    "Drone ID is the ID of the drone you want to interact with, "
    "it starts at 0\n"
    "\t/pause\n"
    "\t/set_freq [freq]\n"
    "\t/tick [time] [unit] (unit: t, s, m, h, d)\n"
    "\t/levelup [drone_id]\n"
    "\t/leveldown [drone_id]\n"
    "\t/setlevel [drone_id] [level]\n"
    "\t/tp [drone_id] [x] [y]\n"
    "\t/setinventory [drone_id] [food] [linemate] [deraumere] [sibur] "
    "[mendiane] [phiras] [thystame]\n"
    "\t/locate [drone_id]\n"
    "\t/getinventory [drone_id]\n"
    "\t/help\n");
    print_and_send(buffer, client);
}
