/*
** EPITECH PROJECT, 2024
** object_manipulation.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Game/game.h"

bool drop_object(client_t *client, server_t *server, char *args)
{
    char *item[7] = {"linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame", "food"};
    tile_t *tile = &server->game->map[client->drone->y][client->drone->x];
    int i = 0;

    while(i < 7) {
        if (strcmp(args, item[i]) == 0)
            break;
        if (i == 6)
            return false;
        i++;
    }
    if (client->drone->inventory[i] == 0)
        return false;
    client->drone->inventory[i] -= 1;
    tile->inventory[i] += 1;
    return true;
}

bool take_object(client_t *client, server_t *server, char *args)
{
    char *item[7] = {"linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame", "food"};
    tile_t *tile = &server->game->map[client->drone->y][client->drone->x];
    int i = 0;

    while(i < 7) {
        if (strcmp(args, item[i]) == 0)
            break;
        if (i == 6)
            return false;
        i++;
    }
    if (tile->inventory[i] == 0)
        return false;
    client->drone->inventory[i] += 1;
    tile->inventory[i] -= 1;
    return true;
}
