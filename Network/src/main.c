/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Parsing/parse_args.h"
#include <stdio.h>

int main(int ac, char **av)
{
    char **args = get_array_from_args(ac, av);
    if (args == NULL)
        return 84;
    for (int i = 0; args[i] != NULL; i++)
        printf("%s\n", args[i]);
    return 0;
    return zappy_network(ac, av);
}
