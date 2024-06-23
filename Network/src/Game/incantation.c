/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Game/game.h"
#include "Game/game_command.h"
#include "Game/game_functions.h"
#include "Server/server.h"
#include "GuiProtocol/gui_event.h"

static int count_players_on_tile_at_lvl(int x, int y, int lvl,
    server_t *server)
{
    int count = 0;
    linked_list_drone_t *tmp = server->game->map[x][y].drone_list;

    while (tmp != NULL) {
        if (tmp->drone->level == lvl)
            count++;
        tmp = tmp->next;
    }
    return count;
}

bool check_incantation_prerequisites(client_t *client, server_t *server)
{
    int count;

    if (client->drone->level > 7)
        return false;
    for (int i = 1; i < 7; i++) {
        if (server->game->map[client->drone->x][client->drone->y].inventory[i]
        < incantation_level_prerequisites[client->drone->level - 1][i])
            return false;
    }
    count = count_players_on_tile_at_lvl(client->drone->x,
        client->drone->y, client->drone->level, server);
    if (count < incantation_level_prerequisites[client->drone->level - 1][0])
        return false;
    return true;
}

client_t *get_client_by_drone_id(int id, server_t *server)
{
    client_list_t *tmp = server->list;

    while (tmp != NULL) {
        if (tmp->client->drone != NULL && tmp->client->drone->id == id)
            return tmp->client;
        tmp = tmp->next;
    }
    return NULL;
}

static void put_everyone_on_tile_to_incantation_lvl(int x, int y, int lvl,
    server_t *server)
{
    linked_list_drone_t *tmp = server->game->map[x][y].drone_list;

    while (tmp != NULL) {
        if (tmp->drone->level == lvl) {
            tmp->drone->incantation_ticks = 299;
            send(get_client_by_drone_id(tmp->drone->id, server)->socket,
                "Elevation underway\n", 19, 0);
        }
        tmp = tmp->next;
    }
}

bool check_incantation_condition(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    bool ret = check_incantation_prerequisites(client, server);

    if (ret == false) {
        send(client->socket, "ko\n", 3, 0);
        return false;
    } else {
        client->drone->incantation_master = true;
        put_everyone_on_tile_to_incantation_lvl(client->drone->x,
            client->drone->y, client->drone->level, server);
        gui_pic(server, client->drone);
        return true;
    }
}

void incantation(client_t *client, server_t *server,
    __attribute__((unused))char **args)
{
    static int highest_lvl = 1;

    printf("Incantation from %s\n", client->drone->team_name);
    if (client->drone->level + 1 > highest_lvl) {
        highest_lvl = client->drone->level + 1;
        server->game->winning_team = client->drone->team_name;
        printf("New highest level: %d\n", highest_lvl);
        if (highest_lvl == 8) {
            printf("Team %s won\n", server->game->winning_team);
            gui_seg(server);
        }
    }
}
