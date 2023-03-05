/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** pwd.c
*/

#include "../include/my.h"

void pwd(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    write(client->socket, "257 \"", 5);
    write(client->socket, client->path, my_strlen(client->path));
    write(client->socket, "\" " , 2);
    write(client->socket, "created.\r\n", 10);
    return;
}
