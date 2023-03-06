/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** quit.c
*/

#include "../include/my.h"

void quit(t_t *this, client_t *client)
{
    server_send(client->socket, "221", msg221);
    close(client->socket);
    client->socket = 0;
    return;
}

//buffer management
//accept pour pasv en décalé
// connect pour port décalé