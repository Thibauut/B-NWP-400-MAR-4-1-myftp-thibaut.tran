/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** cdup.c
*/

#include "../include/my.h"

void cdup(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    client->path = strcat(client->path, "/..");
    char *tmp = realpath(client->path, NULL);
    if (tmp == NULL || chdir(tmp) == -1) {
        server_send(client->socket, "550", "Failed to change directory.");
        return;
    }
    free(client->path);
    client->path = strdup(tmp);
    server_send(client->socket, "250", msg250);
}
