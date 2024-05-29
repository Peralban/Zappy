/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** DESCRIPTION
*/

#include "Server/server.h"
#include "Parsing/parse_args.h"
#include <stdio.h>

static int print_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2"
    " ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\tis the reciprocal of time unit for execution of "
    "actions\n");
    return 0;
}

int main(int ac, char **av)
{
    char **args = NULL;

    if (ac == 2 && (strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h") == 0))
        return print_help();
    args = get_array_from_args(ac, av);
    if (args == NULL)
        return 84;
    return zappy_network(args);
}
