/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** port.c
*/

#include "../include/my.h"

void port(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (client->mode == ACTIVE) {
        server_send(client->socket, "500",
        "PORT command already used. Use PASV to switch to passive mode.");
        return;
    }
}
