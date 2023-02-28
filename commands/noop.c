/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** noop.c
*/

#include "../include/my.h"

void noop(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Not logged in.");
        return;
    }
    server_send(client->socket, "200", msg200);
    return;
}
