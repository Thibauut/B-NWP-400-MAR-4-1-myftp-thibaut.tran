/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** utils_linklist.c
*/

#include "../include/my.h"

my_list_t *free_element_at(my_list_t *list, int pos)
{
    my_list_t *prev = list;
    my_list_t *curr = list;
    if (list == NULL)
        return (NULL);
    if (pos == 0) {
        list = free_first_element(list);
        return list;
    }
    for (int i = 0; i < pos; i += 1) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr);
    return (list);
}

void print_list(my_list_t *list)
{
    for (; list != NULL; list = list->next)
        printf("%d\n", list->client->socket);
}

my_list_t *create_cell(client_t *client)
{
    my_list_t *cell = malloc(sizeof(my_list_t));
    if (cell == NULL)
        return (NULL);
    cell->client = malloc(sizeof(client_t));
    cell->client->username = client->username;
    cell->client->password = client->password;
    cell->client->is_log = client->is_log;
    cell->client->socket = client->socket;
    cell->client->data_socket = client->data_socket;
    cell->client->data_addr = client->data_addr;
    cell->client->data_port = client->data_port;
    cell->client->data_ip = client->data_ip;
    cell->client->mode = client->mode;
    cell->client->path = client->path;
    cell->next = NULL;
    return (cell);
}

my_list_t *add_element(my_list_t *list, client_t *client, int pos)
{
    my_list_t *prev = list;
    my_list_t *curr = list;
    my_list_t *cell = create_cell(client);
    if (list == NULL)
        return (cell);
    if (pos == 0) {
        cell->next = list;
        return (cell);
    }
    for (int i = 0; i < pos; i += 1) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = cell;
    cell->next = curr;
    return (list);
}

client_t *get_element(my_list_t *list, int pos)
{
    for (int i = 0; i < pos; i += 1)
        list = list->next;
    return (list->client);
}
