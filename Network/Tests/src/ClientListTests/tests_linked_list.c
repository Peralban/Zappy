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
    free(list);
}

Test(create_client, should_return_valid_client)
{
    struct sockaddr_in *Address = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, Address);
    cr_assert_not_null(client);
    cr_assert_eq(client->clientServer->socket, 1);
    cr_assert_eq(client->clientServer->clientAddress, Address);
    free(client->clientServer);
    free(client);
}

Test(add_client_to_list, should_add_client_to_list)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *Address = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, Address);
    int result = add_client_to_list(&list, client);
    cr_assert_eq(result, 0);
    cr_assert_eq(list->client, client);
    free(client->clientServer);
    free(client);
    free(list);
}

Test(remove_client_from_list, should_remove_client_from_list)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *Address = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, Address);
    add_client_to_list(&list, client);
    remove_client_from_list(&list, client);
    cr_assert_null(list->client);
    free(client->clientServer);
    free(client);
    free(list);
}

Test(get_client_from_list, should_return_null_when_list_is_empty)
{
    client_list_t *list = create_client_list();
    cr_assert_null(get_client_from_list(list, 1));
    free(list);
}

Test(get_client_from_list, should_return_client_when_found)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *Address = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, Address);
    add_client_to_list(&list, client);
    cr_assert_eq(get_client_from_list(list, 1), client);
}

Test(eject_client_from_server, should_remove_client_from_server)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *Address = malloc(sizeof(struct sockaddr_in));
    client_t *client = create_client(1, Address);
    server_t *server = malloc(sizeof(server_t));
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    FD_SET(client->clientServer->socket, &server->readfds);
    FD_SET(client->clientServer->socket, &server->writefds);
    add_client_to_list(&list, client);
    eject_client_from_server(client, &list, &server);
    cr_assert_null(get_client_from_list(list, 1));
    cr_assert_eq(FD_ISSET(client->clientServer->socket, &server->readfds), 0);
    cr_assert_eq(FD_ISSET(client->clientServer->socket, &server->writefds), 0);
    free(client->clientServer);
    free(client);
    free(list);
    free(server);
}

Test(destroy_client_list, should_free_all_clients_in_list)
{
    client_list_t *list = create_client_list();
    struct sockaddr_in *Address = malloc(sizeof(struct sockaddr_in));
    client_t *client1 = create_client(1, Address);
    client_t *client2 = create_client(2, Address);
    add_client_to_list(&list, client1);
    add_client_to_list(&list, client2);
    destroy_client_list(list);
    // The list and its clients have been freed, so there's nothing to assert here.
    // If destroy_client_list works correctly, this test won't cause a memory leak.
}