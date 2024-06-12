/*
** EPITECH PROJECT, 2024
** Zappy_Server
** File description:
** No file there , just an epitech header example .
*/

#pragma once

#include "Server/server.h"

typedef enum {
    GUI_PNW = 1,
    GUI_PEX,
    GUI_PBC,
    GUI_PIC,
    GUI_PIE,
    GUI_PFK,
    GUI_PDR,
    GUI_PGT,
    GUI_PDI,
    GUI_ENW,
    GUI_EBO,
    GUI_EDI,
    GUI_SEG,
    GUI_SMG,
    GUI_SUC,
    GUI_SBP
} event_type_e;

void gui_event(event_type_e event, server_t *server, void *data);

void send_all_graphics(server_t *server, char *str);

typedef struct {
    event_type_e event_type;
    void (*function)(server_t *server, void *data);
} event_gui_t;

void pnw(server_t *server, void *data);

void suc(server_t *server, void *data);

static const event_gui_t event_gui[] = {
    {GUI_PNW, &pnw},
    //{GUI_PEX, &pex},
    //{GUI_PBC, &pbc},
    //{GUI_PIC, &pic},
    //{GUI_PIE, &pie},
    //{GUI_PFK, &pfk},
    //{GUI_PDR, &pdr},
    //{GUI_PGT, &pgt},
    //{GUI_PDI, &pdi},
    //{GUI_ENW, &enw},
    //{GUI_EBO, &ebo},
    //{GUI_EDI, &edi},
    //{GUI_SEG, &seg},
    //{GUI_SMG, &smg},
    {GUI_SUC, &suc},
    //{GUI_SBP, &sbp},
    {0, NULL}
};