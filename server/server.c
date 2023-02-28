/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** server.c
*/

#include "../include/my.h"

void server_send(int clientSocket, char *digitCode, char *msg)
{
    write(clientSocket, digitCode, my_strlen(digitCode));
    write(clientSocket, " ", 1);
    write(clientSocket, msg, my_strlen(msg));
    write(clientSocket, "\r\n", 2);
}

void commands(t_t *this, client_t *client)
{
    if (this->cmd == NULL) {
        server_send(client->socket, "500", msg500);
        return;
    } else if (do_commands(this, client) == 0)
        return;
    server_send(client->socket, "500", msg500);
}

void read_data(t_t *this, client_t *client)
{
    int readValue = 0;
    char buffer[1024] = "\0";
    if ((readValue = read(client->socket, buffer, 1024)) == 0) {
        close(client->socket);
        client->socket = 0;
    } else {
        this->cmd = NULL;
        this->cmd = strtok_wordtab(buffer, "  \t\n\r");
        commands(this, client);
    }
}

void data_from_client(t_t *this)
{
    my_list_t *tmp = this->cList;
    for (int i = 0; tmp != NULL; i++, tmp = tmp->next) {
        if (FD_ISSET(tmp->client->socket, &this->tmpfds))
            read_data(this, tmp->client);
    }
}

void server_loop(t_t *this)
{
    int _activity;
    this->maxfd = this->control_socket;
    while (1) {
        this->tmpfds = this->readfds;
        add_client_to_set(this);
        _activity = select(this->maxfd + 1, &this->tmpfds, NULL, NULL, NULL);
        select_error(_activity);
        handle_new_connection(this);
        data_from_client(this);
    }
}
