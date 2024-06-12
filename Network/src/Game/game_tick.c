/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "Server/server.h"
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

void game_tick(server_t *server)
{
    static uint64_t last_tick_time = 0;
    uint64_t current_time = get_time();

    if (current_time - last_tick_time >=
        (1000000 / (uint64_t)server->info_game.freq)) {
        update_players(server);
        server->game->spawn_tick++;
        last_tick_time = current_time;
    }
    if (server->game->spawn_tick >= 20) {
        server->game->spawn_tick = 0;
        spawn_resources(server);
    }
}
