/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** commands_utils.c
*/

#include "../include/my.h"

int accept_to_data(t_t *this, client_t *client)
{
    socklen_t data_socket_len = sizeof(client->data_addr);
    int tmpsock = accept(client->data_socket,
    (struct sockaddr *)&client->data_addr, &data_socket_len);
    return tmpsock;
}

int connect_to_data(t_t *this, client_t *client)
{
    socklen_t data_socket_len = sizeof(client->data_addr);
    int is_connected = connect(client->data_socket,
    (struct sockaddr *)&client->data_addr, data_socket_len);
    return is_connected;
}
