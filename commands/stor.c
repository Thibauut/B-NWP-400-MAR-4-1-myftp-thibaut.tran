/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** stor.c
*/

#include "../include/my.h"

void stor_file(t_t *this, client_t *client, FILE *file, int tmpsock)
{
    char buffer[1];
    server_send(client->socket, "150", msg150);
    while (read(tmpsock, buffer, 1) > 0)
        fwrite(buffer, 1, 1, file);
    fclose(file);
    server_send(client->socket, "226",
    "Transfer complete. Closing data connection.");
}

int stor_is_file(t_t *this, client_t *client, FILE *file)
{
    if (file == NULL) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return 1;
    }
    return 0;
}

void stor_exec_mode(t_t *this, client_t *client, FILE *file)
{
    int tmpsock;
    if (client->mode == ACTIVE) {
        tmpsock  = connect_to_data(this, client);
        stor_file(this, client, file, client->data_socket);
        client->mode = NONE;
        close(client->data_socket);
        return;
    }
    if (client->mode == PASSIVE) {
        tmpsock = accept_to_data(this, client);
        stor_file(this, client, file, tmpsock);
        client->mode = NONE;
        close(tmpsock);
        close(client->data_socket);
        return;
    }
}

void stor(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (client->mode == NONE) {
        server_send(client->socket, "425", "Use PORT or PASV first.");
        return;
    }
    FILE *file = fopen(this->cmd[1], "wb");
    if (stor_is_file(this, client, file) == 1)
        return;
    stor_exec_mode(this, client, file);
    return;
}
