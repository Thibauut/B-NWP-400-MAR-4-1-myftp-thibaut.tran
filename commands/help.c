/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** help.c
*/

#include "../include/my.h"

void help(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    server_send(client->socket, "214", "Following commands are recognized.");
    write(client->socket, "USER PASS CWD CDUP QUIT DELE PWD\r\n", 34);
    write(client->socket, "PASV PORT HELP NOOP RETR STOR LIST\r\n", 36);
    server_send(client->socket, "214", "End of help.");
}
