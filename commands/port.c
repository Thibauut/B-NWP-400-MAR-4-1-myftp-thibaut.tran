/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** port.c
*/

#include "../include/my.h"

int get_ip(t_t *this, client_t *client, char **info, char **ip)
{
    char *tmp = malloc(sizeof(char) * 1024);
    if (info[0] == NULL || info[1] == NULL || info[2] == NULL
    || info[3] == NULL)
        return 1;
    tmp = strcat(tmp, info[0]);
    tmp = strcat(tmp, ".");
    tmp = strcat(tmp, info[1]);
    tmp = strcat(tmp, ".");
    tmp = strcat(tmp, info[2]);
    tmp = strcat(tmp, ".");
    tmp = strcat(tmp, info[3]);
    struct in_addr addr;
    if (inet_aton(tmp, &addr) == 0)
        return 1;
    *ip = strdup(tmp);
    return 0;
}

int get_port(t_t *this, client_t *client, char **info, int *port)
{
    if (info[4] == NULL || info[5] == NULL)
        return 1;
    if (my_is_number(info[4]) == 1 || my_is_number(info[5]) == 1)
        return 1;
    *port = atoi(info[4]) * 256 + atoi(info[5]);
    if (*port < 0 || *port > 65535)
        return 1;
    return 0;
}

int get_info(t_t *this, client_t *client, char **ip, int *port)
{
    char **info = strtok_wordtab(this->cmd[1], ",\r\n");
    if (this->cmd[1] == NULL ||
    (this->cmd[1] != NULL && this->cmd[2] != NULL)) {
        server_send(client->socket, "501",
        "Syntax error in parameters or arguments.");
        return 1;
    }
    if (get_ip(this, client, info, ip) == 1 ||
    get_port(this, client, info, port) == 1) {
        server_send(client->socket, "501",
        "Syntax error in parameters or arguments.");
        return 1;
    }
    return 0;
}

int init_port(t_t *this, client_t *client, char *ip, int port)
{
    client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->data_socket == -1) {
        server_send(client->socket, "425", "Can't open data connection.");
        return 1;
    }
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_addr.s_addr = inet_addr(ip);
    client->data_addr.sin_port = htons(port);
    return 0;
}

void port(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (client->mode == ACTIVE) {
        server_send(client->socket, "500",
        "PORT command already used. Use PASV to switch to passive mode.");
        return;
    }
    char *ip;
    int port;
    if (get_info(this, client, &ip, &port) == 1
    || init_port(this, client, ip, port) == 1)
        return;
    client->mode = ACTIVE;
    server_send(client->socket, "200", msg200);
    return;
}
