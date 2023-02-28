/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** init_server.c
*/

#include "../include/my.h"

void init_fdset(t_t *this)
{
    FD_ZERO(&this->readfds);
    FD_ZERO(&this->tmpfds);
    FD_SET(this->control_socket, &this->readfds);
}

void init_socket(t_t* this)
{
    this->control_socket = socket(AF_INET, SOCK_STREAM, 0);
    socket_error(this->control_socket);
    this->control_addr.sin_family = AF_INET;
    this->control_addr.sin_addr.s_addr = INADDR_ANY;
    this->control_addr.sin_port = htons(this->port);
    htons_error(this);
    int _bind = bind(this->control_socket, (SOCKADDR *)
    &this->control_addr, sizeof(this->control_addr));
    bind_error(_bind);
    int _listen = listen(this->control_socket, MAX_CLIENTS);
    listen_error(_listen);
}

void my_server(t_t *this)
{
    init_socket(this);
    init_fdset(this);
    server_loop(this);
}
