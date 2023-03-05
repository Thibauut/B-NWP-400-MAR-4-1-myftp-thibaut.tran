/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** new_client.c
*/

#include "../include/my.h"

void add_client_to_set(t_t *this)
{
    my_list_t *tmp = this->cList;
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->client->socket > 0) {
            FD_SET(tmp->client->socket, &this->tmpfds);
            (tmp->client->socket > this->maxfd) ?
                this->maxfd = tmp->client->socket : 0;
        }
    }
}

void new_client(t_t *this)
{
    my_list_t *tmp = this->cList;
    for (int i = 0; tmp != NULL; i++, tmp = tmp->next) {
        if (tmp->client->socket == 0) {
            tmp->client->socket = this->new_socket;
            server_send(tmp->client->socket, "220", msg220);
            break;
        }
    }
}

client_t *create_client(t_t *this)
{
    client_t *newclient = malloc(sizeof(client_t));
    newclient->username = NULL;
    newclient->password = NULL;
    newclient->is_log = false;
    newclient->socket = 0;
    newclient->data_socket = 0;
    newclient->data_port = 0;
    newclient->data_ip = NULL;
    newclient->mode = NONE;
    newclient->path = strdup(this->path);
    return (newclient);
}

void handle_new_connection(t_t *this)
{
    if (FD_ISSET(this->control_socket, &this->tmpfds)) {
        socklen_t client_addr_len = sizeof(this->client_addr);
        if ((this->new_socket = accept(this->control_socket,
        (struct sockaddr *)&this->client_addr, &client_addr_len)) < 0) {
            perror("accept failed");
            exit(84);
        }
        client_t *newclient = create_client(this);
        this->cList = add_element(this->cList, newclient, 0);
        new_client(this);
    }
}
