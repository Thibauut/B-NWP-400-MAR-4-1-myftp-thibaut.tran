/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** error.c
*/

#include "../include/my.h"

void socket_error(int control_socket)
{
    if (control_socket < 0) {
        perror("socket()");
        exit(84);
    }
}

void htons_error(t_t *this)
{
    if (htons(this->port) == 0) {
        perror("htons()");
        exit(84);
    }
}

void bind_error(int _bind)
{
    if (_bind < 0) {
        perror("bind()");
        exit(84);
    }
}

void listen_error(int _listen)
{
    if (_listen < 0) {
        perror("listen()");
        exit(84);
    }
}

void select_error(int _activity)
{
    if ((_activity < 0) && (errno != EINTR)) {
        perror("select()");
        exit(84);
    }
}
