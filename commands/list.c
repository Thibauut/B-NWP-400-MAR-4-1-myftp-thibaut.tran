/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** list.c
*/

#include "../include/my.h"

void list(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (client->mode == NONE) {
        server_send(client->socket, "425", "Use PORT or PASV first.");
        return;
    }
}
