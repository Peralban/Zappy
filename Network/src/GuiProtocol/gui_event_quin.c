/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "GuiProtocol/gui_event.h"

void gui_seg(server_t *server)
{
    static bool already_sent = false;
    char buffer[1024] = {0};

    if (server->game->winning_team == NULL)
        return;
    if (already_sent)
        return;
    already_sent = true;
    sprintf(buffer, "seg %s\n", server->game->winning_team);
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
