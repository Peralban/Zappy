/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "Game/game_functions.h"
#include "Game/game.h"
#include <stdlib.h>
#include "GuiProtocol/gui_event.h"

void remove_egg_elem(linked_list_egg_t *egg, linked_list_egg_t **list)
{
    linked_list_egg_t *tmp = *list;

    while (tmp != NULL && tmp != egg)
        tmp = tmp->next;
    if (tmp == NULL)
        return;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp == *list)
        *list = tmp->next;
    free(tmp);
}

static int count_egg(linked_list_egg_t *list, char *team_name)
{
    linked_list_egg_t *tmp = list;
    int n = 0;

    while (tmp != NULL) {
        if (tmp->egg->team_name == team_name)
            n++;
        tmp = tmp->next;
    }
    return n;
}

static egg_t *pick_random_egg(linked_list_egg_t **list, char *team_name)
{
    linked_list_egg_t *tmp = *list;
    egg_t *egg = NULL;
    int n = count_egg(*list, team_name);
    int r = rand() % n;

    while (tmp != NULL) {
        if (tmp->egg->team_name == team_name && r == 0) {
            egg = tmp->egg;
            remove_egg_elem(tmp, list);
            return egg;
        }
        if (tmp->egg->team_name == team_name) {
            r--;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void spawn_on_egg(server_t *server, drone_t *drone, char *team_name)
{
    egg_t *egg = pick_random_egg(&server->game->egg_list, team_name);

    gui_ebo(server, egg);
    drone->x = egg->x;
    drone->y = egg->y;
    free(egg);
}
