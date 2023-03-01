/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** user.c
*/

#include "../include/my.h"

void user(t_t *this, client_t *client)
{
    if (client->is_log == true) {
        server_send(client->socket, "530", "User already logged in.");
        return;
    }
    if (client->is_log == false && this->cmd[1] == NULL) {
        server_send(client->socket, "501",
        "Syntax error in parameters or arguments.");
        return;
    }
    server_send(client->socket, "331", msg331);
    client->username = strdup(this->cmd[1]);
    return;
}
