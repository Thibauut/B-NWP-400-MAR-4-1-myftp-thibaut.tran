/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** pass.c
*/

#include "../include/my.h"

void login(t_t *this, client_t *client)
{
    if (client->is_log == true) {
        server_send(client->socket, "530", "User already logged in.");
        return;
    }
    if (my_strcmp(client->username, "Anonymous") != 0) {
        server_send(client->socket, "530", "Need account for login.");
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
    server_send(client->socket, "530", "Login with USER first.");
}
