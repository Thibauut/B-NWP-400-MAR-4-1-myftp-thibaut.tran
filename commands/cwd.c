/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** cwd.c
*/

#include "../include/my.h"

int change_dir(t_t *this, client_t *client)
{
    char *tmp = strdup(client->path);
    tmp = my_strcat(tmp, "/");
    tmp = my_strcat(tmp, this->cmd[1]);
    char *new_path = realpath(tmp, NULL);
    if (chdir(new_path) == -1 || new_path == NULL)
        return 1;
    client->path = strdup(tmp);
    return 0;
}

void cwd(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (this->cmd[1] == NULL || (this->cmd[1] != NULL && this->cmd[2] != NULL)
    || change_dir(this, client) == 1) {
        server_send(client->socket, "501",
        "Syntax error in parameters or arguments.");
        return;
    }
    server_send(client->socket, "250", msg250);
}
