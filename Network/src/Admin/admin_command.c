/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** No file there , just an epitech header example .
*/

#include "Admin/admin_function.h"
#include "Server/server.h"
#include "lib/my.h"
#include <stdio.h>

static void exec_one_admin_command(client_t *client, server_t *server,
    char *command)
{
    char **command_args = my_str_to_word_array(command, " ");
    int len = my_array_len(command_args);

    printf("Admin command: %s\n", command_args[0]);
    for (int j = 0; commands_admin[j].name != NULL; j++) {
        if (strcmp(command_args[0], commands_admin[j].name) != 0)
            continue;
        if (len == 1 + commands_admin[j].nb_args)
            commands_admin[j].function(client, server, command_args + 1);
        else
            //gui_sbp(client->socket);
            printf("sbp\n");
        my_free_array(command_args);
        return;
    }
    //gui_suc(client->socket);
    printf("suc\n");
    my_free_array(command_args);
}

void exec_admin_commands(client_t *client, server_t *server, char *buffer)
{
    char **commands_arr = my_str_to_word_array(buffer, "\n");

    for (int i = 0; commands_arr[i] != NULL; i++)
        exec_one_admin_command(client, server, commands_arr[i]);
    my_free_array(commands_arr);
}
