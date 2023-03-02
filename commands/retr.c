/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** retr.c
*/

#include "../include/my.h"

void send_file(t_t *this, client_t *client, FILE *file)
{
    char buffer[1024];
    int size = 0;
    while ((size = fread(buffer, 1, 1024, file)) > 0)
        write(client->data_socket, buffer, size);
    fclose(file);
    server_send(client->socket, "226",
    "Transfer complete. Closing data connection.");
    client->mode = NONE;
    close(client->data_socket);
}

int retr_open_file(t_t *this, client_t *client,FILE *file)
{
    if (file == NULL) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return 1;
    }
    return 0;
}

int retr_file_check(t_t *this, client_t *client)
{
    if (access(this->cmd[1], F_OK) == -1 || access(this->cmd[1], R_OK) == -1) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return 1;
    }
    return 0;
}

void retr(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (client->mode == NONE) {
        server_send(client->socket, "425", "Use PORT or PASV first.");
        return;
    }
    FILE* file = fopen(this->cmd[1], "rb");
    if (retr_file_check(this, client) == 1 ||
    retr_open_file(this, client, file) == 1)
        return;
    server_send(client->socket, "150", msg150);
    send_file(this, client, file);
    return;
}
