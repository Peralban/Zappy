/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** test.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ClientList/client_list.h"

Test(create_client_list, test1)
{
    client_list_t *list = create_client_list();

    if (list->client == NULL && list->next == NULL && list->prev == NULL)
        cr_assert_eq(1, 1);
    else
        cr_assert_fail();
}

Test(create_client, test2)
{
    struct sockaddr_in *clientAddress = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, clientAddress);

    if (client->clientServer->socket == 1 && client->clientServer->clientAddress == clientAddress)
        cr_assert_eq(1, 1);
    else
        cr_assert_fail();
}

Test(add_client_to_list, test3)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *clientAddress = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, clientAddress);

    add_client_to_list(&list, client);
    if (list->client->clientServer->socket == 1 && list->client->clientServer->clientAddress == clientAddress)
        cr_assert_eq(1, 1);
    else
        cr_assert_fail();
}

Test(remove_client_from_list, test4)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *clientAddress = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, clientAddress);

    add_client_to_list(&list, client);
    remove_client_from_list(&list, client);
    if (list->client == NULL && list->next == NULL && list->prev == NULL)
        cr_assert_eq(1, 1);
    else
        cr_assert_fail();
}
