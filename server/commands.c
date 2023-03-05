/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** commands.c
*/

#include "../include/my.h"

int file_commands(t_t *this, client_t *client)
{
    if (my_strcasecmp(this->cmd[0], "RETR") == 0) {
        retr(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "STOR") == 0) {
        stor(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "LIST") == 0) {
        list(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "DELE") == 0) {
        dele(this, client);
        return 0;
    }
    return 1;
}

int login_commands(t_t *this, client_t *client)
{
    if (my_strcasecmp(this->cmd[0], "USER") == 0) {
        user(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "PASS") == 0) {
        pass(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "CWD") == 0) {
        cwd(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "CDUP") == 0) {
        cdup(this, client);
        return 0;
    }
    return 1;
}

int transfer_commands(t_t *this, client_t *client)
{
    if (my_strcasecmp(this->cmd[0], "PORT") == 0) {
        port(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "PASV") == 0) {
        pasv(this, client);
        return 0;
    }
    return 1;
}

int utils_commands(t_t *this, client_t *client)
{
    if (my_strcasecmp(this->cmd[0], "QUIT") == 0) {
        quit(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "NOOP") == 0) {
        noop(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "HELP") == 0) {
        help(this, client);
        return 0;
    }
    if (my_strcasecmp(this->cmd[0], "PWD") == 0) {
        pwd(this, client);
        return 0;
    }
    return 1;
}

int do_commands(t_t *this, client_t *client)
{
    if (utils_commands(this, client) == 0)
        return 0;
    if (login_commands(this, client) == 0)
        return 0;
    if (transfer_commands(this, client) == 0)
        return 0;
    if (file_commands(this, client) == 0)
        return 0;
    return 1;
}
