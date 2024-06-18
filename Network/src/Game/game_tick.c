/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "Server/server.h"
#include "ClientList/client_list.h"
#include <sys/time.h>

static uint64_t get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}

static void spawn_resources(server_t *server)
{
    int x;
    int y;

    for (int k = 0; k < MAX_ITEMS; k++) {
        for (int i = 0; i < server->game->picked_up_items[k] &&
        server->game->picked_up_items[k] > 0; i++) {
            x = rand() % server->info_game.width;
            y = rand() % server->info_game.height;
            server->game->map[x][y].inventory[k]++;
        }
        if (server->game->picked_up_items[k] > 0) {
            server->game->picked_up_items[k] = 0;
        }
    }
}

static void remove_dead_players(server_t *server)
{
    for (client_list_t *tmp = server->list; tmp != NULL; tmp = tmp->next) {
        if (tmp->client == NULL)
            continue;
        if (tmp->client->drone == NULL && tmp->client->state == PLAYING) {
            eject_client_from_server(tmp->client, server);
            remove_dead_players(server);
            return;
        }
    }
}

void game_tick_action(server_t *server)
{
    update_players(server);
    remove_dead_players(server);
    server->game->spawn_tick++;
    if (server->game->spawn_tick >= 20) {
        server->game->spawn_tick = 0;
        spawn_resources(server);
    }
}

void game_tick(server_t *server)
{
    static uint64_t last_tick_time = 0;
    uint64_t ticks;

    if (last_tick_time == 0)
        last_tick_time = get_time();
    if (server->game->paused)
        return;
    ticks = (1000000 / (uint64_t)server->info_game.freq);
    for (uint64_t current_time = get_time();
    current_time - last_tick_time >= ticks; last_tick_time += ticks) {
        game_tick_action(server);
    }
}
