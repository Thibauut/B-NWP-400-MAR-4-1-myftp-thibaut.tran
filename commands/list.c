/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** list.c
*/

#include "../include/my.h"

char *get_list_cmd(t_t *this, client_t *client)
{
    char *cmd = malloc(sizeof(char) * 1024);
    if (this->cmd[1] != NULL) {
        cmd = strcat(cmd, "ls -l");
        cmd = strcat(cmd, " ");
        cmd = strcat(cmd, this->cmd[1]);
        return cmd;
    }
    cmd = strdup("ls -l");
    return cmd;
}

void exec_list(t_t *this, client_t *client, char *cmd)
{
    FILE *file;
    char buffer[1024];
    size_t size = 0;
    file = popen(cmd, "r");
    server_send(client->socket, "150", msg150);
    while ((size = fread(buffer, 1, 1024, file)) > 0)
        write(client->data_socket, buffer, size);
    pclose(file);
    server_send(client->socket, "226", msg226);
    close(client->data_socket);
}

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
    if (this->cmd[2] != NULL) {
        server_send(client->socket, "501",
        "Syntax error in parameters or arguments.");
        return;
    }
    char *cmd = get_list_cmd(this, client);
    exec_list(this, client, cmd);
    client->mode = NONE;
    return;
}
