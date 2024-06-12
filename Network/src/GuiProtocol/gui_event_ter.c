/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void gui_pfk(server_t *server, int id)
{
    char buffer[1024] = {0};

    sprintf(buffer, "pfk %d\n", id);
    send_all_graphics(server, buffer);
}

void gui_pdr(server_t *server, int id, int item)
{
    char buffer[1024] = {0};

    sprintf(buffer, "pdr %d %d\n", id, item);
    send_all_graphics(server, buffer);
}

void gui_pgt(server_t *server, int id, int item)
{
    char buffer[1024] = {0};

    sprintf(buffer, "pgt %d %d\n", id, item);
    send_all_graphics(server, buffer);
}

void gui_pdi(server_t *server, int id)
{
    char buffer[1024] = {0};

    sprintf(buffer, "pdi %d\n", id);
    send_all_graphics(server, buffer);
}
