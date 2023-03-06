/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** stor.c
*/

#include "../include/my.h"

void stor_file(t_t *this, client_t *client, FILE *file)
{
    char buffer[1];
    while (read(client->data_socket, buffer, 1) > 0)
        fwrite(buffer, 1, 1, file);
    fclose(file);
    server_send(client->socket, "226",
    "Transfer complete. Closing data connection.");
    close(client->data_socket);
}

int stor_is_file(t_t *this, client_t *client, FILE *file)
{
    if (file == NULL) {
        server_send(client->socket, "550", "File not found or inaccessible.");
        return 1;
    }
    return 0;
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
    server_send(client->socket, "150", msg150);
    stor_file(this, client, file);
    client->mode = NONE;
    return;
}
