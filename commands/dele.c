/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** dele.c
*/

#include "../include/my.h"

int is_file(t_t *this, client_t *client, int file)
{
    struct stat st;
    if (file < 0) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return 1;
    }
    if ((fstat(file, &st) == -1
    || !S_ISREG(st.st_mode))) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return 1;
    }
    return 0;
}

char *get_file_path(t_t *this, client_t *client)
{
    char *tmp = strdup(client->path);
    tmp = my_strcat(tmp, "/");
    tmp = my_strcat(tmp, this->cmd[1]);
    char *new_path = realpath(tmp, NULL);
    return new_path;
}

void dele(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (this->cmd[2] != NULL) {
        server_send(client->socket, "501",
        "Syntax error in parameters or arguments.");
        return;
    }
    char *tmp = get_file_path(this, client);
    int file = open(tmp, O_RDONLY);
    if (is_file(this, client, file) == 1)
        return;
    close(file);
    if (remove(this->cmd[1]) == -1) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return;
    }
    server_send(client->socket, "250", msg250);
}
