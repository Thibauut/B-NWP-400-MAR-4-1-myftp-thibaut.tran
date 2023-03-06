/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** retr.c
*/

#include "../include/my.h"

void send_file(t_t *this, client_t *client, int file)
{
    char buffer[1];
    while (read(file, buffer, 1) > 0)
        write(client->data_socket, buffer, 1);
    close(file);
    server_send(client->socket, "226",
    "Transfer complete. Closing data connection.");
    close(client->data_socket);
}

int retr_is_file(t_t *this, client_t *client, int file)
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
    int file = open(this->cmd[1], O_RDONLY);
    if (retr_is_file(this, client, file) == 1)
        return;
    server_send(client->socket, "150", msg150);
    send_file(this, client, file);
    client->mode = NONE;
    return;
}
