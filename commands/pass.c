/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** pass.c
*/

#include "../include/my.h"

void login(t_t *this, client_t *client)
{
    client->password = NULL;
    if (client->is_log == true) {
        server_send(client->socket, "530", "Not logged in.");
        return;
    }
    if (strncmp(client->username, "Anonymous", 9) != 0) {
        server_send(client->socket, "332", "Need account for login.");
        return;
    }
    server_send(client->socket, "230", msg230);
    client->is_log = true;
    if (this->cmd[1] != NULL)
        client->password = strdup(this->cmd[1]);
    return;
}

void pass(t_t *this, client_t *client)
{
    if (client->is_log == false && client->username != NULL) {
        login(this, client);
        return;
    }
    server_send(client->socket, "530", "Enter username first.");
}