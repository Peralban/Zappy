/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void gui_seg(server_t *server, char *team_name)
{
    char buffer[1024] = {0};

    sprintf(buffer, "seg %s\n", team_name);
    send_all_graphics(server, buffer);
}

void gui_smg(server_t *server, char *msg)
{
    char buffer[1024] = {0};

    sprintf(buffer, "smg %s\n", msg);
    send_all_graphics(server, buffer);
}

void gui_suc(int socket)
{
    send(socket, "suc\n", 4, 0);
}

void gui_sbp(int socket)
{
    send(socket, "sbp\n", 4, 0);
}
