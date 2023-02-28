/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** user.c
*/

#include "../include/my.h"

void user(t_t *this, client_t *client)
{
    client->username = NULL;
    client->is_log = false;
    if (client->is_log == true) {
        server_send(client->socket, "230", "Already logged in.");
        return;
    }
    if (client->is_log == false && this->cmd[1] == NULL) {
        server_send(client->socket, "530", "Enter an username.");
        return;
    }
    server_send(client->socket, "331", msg331);
    client->username = strdup(this->cmd[1]);
    return;
}
