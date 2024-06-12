/*
** EPITECH PROJECT, 2024
** game_info_cmd.c
** File description:
** DESCRIPTION
*/

#include "Game/game.h"
#include "Server/server.h"

void map_size_cmd(server_t *server, client_t *client, char **args)
{
    char *return_str = calloc(1024, sizeof(char));

    (void)args;
    sprintf(return_str, "msz %d %d\n", server->info_game.width,
        server->info_game.height);
    send(client->socket, return_str, strlen(return_str), 0);
    free(return_str);
}

static char *get_tile_content_at(tile_t *tile, int x, int y)
{
    char *return_str = calloc(128, sizeof(char));

    sprintf(return_str, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        tile->inventory[0], tile->inventory[1], tile->inventory[2],
        tile->inventory[3], tile->inventory[4], tile->inventory[5],
        tile->inventory[6]);
    return return_str;
}

void one_tile_content(server_t *server, client_t *client, char **args)
{
    char *return_str = NULL;
    int x = atoi(args[1]);
    int y = atoi(args[2]);

    if (x < 0 || x >= server->info_game.width || y < 0 ||
        y >= server->info_game.height) {
        send(client->fd, "sbp\n", 4, 0);
        return;
    }
    return_str = get_tile_content_at(&(server->game->map[x][y]), x, y);
    send(client->socket, return_str, strlen(return_str), 0);
    free(return_str);
}

void get_map_content(server_t *server, client_t *client, char **args)
{
    char *return_str = calloc(128 * server->info_game.width *
        server->info_game.height, sizeof(char));
    char *tmp = NULL;

    for (int i = 0; i < server->info_game.width; i++)
        for (int j = 0; j < server->info_game.height; j++) {
            tmp = get_tile_content_at(&(server->game->map[i][j]), i, j);
            strcat(return_str, tmp);
            free(tmp);
        }
    send(client->socket, return_str, strlen(return_str), 0);
    free(return_str);
}

static int get_teams_size(server_t *server)
{
    int size = 0;

    for (int i = 0; i < server->info_game.nb_teams; i++)
        size += strlen(server->game->teams[i].name) + 5;
    return size;
}

void get_all_teams(server_t *server, client_t *client, char **args)
{
    char *return_str = calloc(get_teams_size(server) + 1, sizeof(char));

    (void)args;
    for (int i = 0; i < server->info_game.nb_teams; i++) {
        strcat(return_str, "tna ");
        strcat(return_str, server->game->teams[i].name);
        strcat(return_str, "\n");
    }
    send(client->socket, return_str, strlen(return_str), 0);
    free(return_str);
}
