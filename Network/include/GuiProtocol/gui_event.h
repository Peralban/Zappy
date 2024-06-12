/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"

void send_all_graphics(server_t *server, char *str);

void gui_pnw(server_t *server, drone_t *drone);
void gui_suc(int socket);
void gui_pex(server_t *server, int id);
void gui_pbc(server_t *server, int id, char *msg);
void gui_pic(server_t *server, drone_t *drone);
void gui_pie(server_t *server, drone_t *drone);
void gui_pfk(server_t *server, int id);
void gui_pdr(server_t *server, int id, int item);
void gui_pgt(server_t *server, int id, int item);
void gui_pdi(server_t *server, int id);
void gui_enw(server_t *server, drone_t *drone, egg_t *egg);
void gui_ebo(server_t *server, egg_t *egg);
void gui_edi(server_t *server, egg_t *egg);
