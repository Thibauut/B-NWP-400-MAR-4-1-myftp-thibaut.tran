/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** pwd.c
*/

#include "../include/my.h"

void pwd(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Not logged in.");
        return;
    }
    char *current = malloc(sizeof(char) * 4096);
    getcwd(current, 4096);
    write(client->socket, "257 \"", 5);
    write(client->socket, current, my_strlen(current));
    write(client->socket, "\" " , 2);
    write(client->socket, "created.\r\n", 10);
    return;
}
