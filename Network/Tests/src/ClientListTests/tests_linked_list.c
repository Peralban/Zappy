/*
** EPITECH PROJECT, 2023
** FTPEW
** File description:
** test.c
*/

#include <criterion/criterion.h>
#include "ClientList/client_list.h"

Test(create_client_list, should_return_valid_list)
{
    client_list_t *list = create_client_list();
    cr_assert_not_null(list);
    cr_assert_null(list->client);
    cr_assert_null(list->next);
    cr_assert_null(list->prev);
}

Test(create_client, should_return_valid_client)
{
    client_t *client = create_client(1);
    cr_assert_not_null(client);
    cr_assert_eq(client->socket, 1);
}

Test(add_client_to_list, should_add_client_to_list)
{
    client_list_t *list = create_client_list();
    client_t *client = create_client(1);
    int result = add_client_to_list(list, client);
    cr_assert_eq(result, 0);
    cr_assert_eq(list->client, client);
}

Test(remove_client_from_list, should_remove_client_from_list)
{
    client_list_t *list = create_client_list();
    client_t *client = create_client(1);
    add_client_to_list(list, client);
    remove_client_from_list(list, client);
    cr_assert_null(list->client);
}

Test(get_client_from_list, should_return_null_when_list_is_empty)
{
    client_list_t *list = create_client_list();
    cr_assert_null(get_client_from_list(list, 1));
}

Test(get_client_from_list, should_return_client_when_found)
{
    client_list_t *list = create_client_list();
    client_t *client = create_client(1);
    add_client_to_list(list, client);
    cr_assert_eq(get_client_from_list(list, 1), client);
}

Test(eject_client_from_server, should_remove_client_from_server)
{
    client_list_t *list = create_client_list();
    client_t *client = create_client(1);
    server_t *server = malloc(sizeof(server_t));
    server->list = list;
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    FD_SET(client->socket, &server->readfds);
    FD_SET(client->socket, &server->writefds);
    add_client_to_list(server->list, client);
    eject_client_from_server(client, server);
    cr_assert_null(get_client_from_list(server->list, 1));
    cr_assert_eq(FD_ISSET(client->socket, &server->readfds), 0);
    cr_assert_eq(FD_ISSET(client->socket, &server->writefds), 0);
}

Test(destroy_client_list, should_free_all_clients_in_list)
{
    client_list_t *list = create_client_list();
    client_t *client1 = create_client(1);
    client_t *client2 = create_client(2);
    add_client_to_list(list, client1);
    add_client_to_list(list, client2);
    destroy_client_list(list);
    // The list and its clients have been freed, so there's nothing to assert here.
    // If destroy_client_list works correctly, this test won't cause a memory leak.
}