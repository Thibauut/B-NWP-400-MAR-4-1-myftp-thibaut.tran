/*
** EPITECH PROJECT, 2022
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** pasv.c
*/

#include "../include/my.h"

int init_pasv(t_t *this, client_t *client)
{
    client->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client->data_socket < 0)
        return 1;
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_addr.s_addr = INADDR_ANY;
    client->data_addr.sin_port = htons(0);
    int _bind = bind(client->data_socket, (SOCKADDR *)
    &client->data_addr, sizeof(client->data_addr));
    if (_bind < 0)
        return 1;
    int _listen = listen(client->data_socket, 1);
    if (_listen < 0)
        return 1;
    return 0;
}

int get_server_info(t_t *this, client_t *client)
{
    socklen_t data_addr_size = sizeof(client->data_addr);
    if (getsockname(client->data_socket, (struct sockaddr *)
    &client->data_addr, &data_addr_size) < 0)
        return 1;
    client->data_port = ntohs(client->data_addr.sin_port);
    client->data_ip = malloc(sizeof(char) * 1024);
    client->data_ip = inet_ntoa(this->client_addr.sin_addr);
    return 0;
}

void pasv_send(t_t *this, client_t *client)
{
    char response[100];
    char **ip = strtok_wordtab(client->data_ip, ".");
    sprintf(response, "227 Entering Passive Mode (%s,%s,%s,%s,%d,%d).\r\n",
        ip[0], ip[1], ip[2], ip[3],
        client->data_port / 256, client->data_port % 256);
    write(client->socket, response, my_strlen(response));
}

void pasv(t_t *this, client_t *client)
{
    if (client->is_log == false) {
        server_send(client->socket, "530", "Please login with USER and PASS.");
        return;
    }
    if (client->mode == PASSIVE) {
        server_send(client->socket, "500",
        "PASV command already used. Use PORT to switch to active mode.");
        return;
    }
    if (init_pasv(this, client) == 1 || get_server_info(this, client) == 1) {
        server_send(client->socket, "425", "Can't open data connection.");
        return;
    }
    client->mode = PASSIVE;
    pasv_send(this, client);
    return;
}
