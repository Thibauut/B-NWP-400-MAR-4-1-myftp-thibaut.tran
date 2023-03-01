/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** my.h
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>
#include <pwd.h>
#include <stdbool.h>

#define h1 "USAGE: ./myftp port path"
#define h2 "       port is the port number on which the server socket listens"
#define h3 "       path is the path to the home directory for the "
#define h4 "Anonymous user"

#define MAX_CLIENTS 10

#define msg120 "Service ready in nnn minutes."
#define msg125 "Data connection already open; transfer starting."
#define msg150 "File status okay; about to open data connection."
#define msg200 "Command okay."
#define msg214 "Help message."
#define msg220 "Service ready for new user."
#define msg221 "Service closing control connection."
#define msg226 "Closing data connection".
#define msg227 "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."
#define msg230 "User logged in, proceed."
#define msg250 "Requested file action okay, completed."
#define msg257 "PATHNAME created."
#define msg331 "User name okay, need password."
#define msg332 "Need account for login."
#define msg500 "Syntax error, command unrecognized."
#define msgxxx "Error (RFC compliant)"

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct passwd passwd;

enum mode {
    NONE,
    ACTIVE,
    PASSIVE
};

typedef struct client_t {
    char *username;
    char *password;
    bool is_log;
    int socket;

    int data_socket;
    int data_port;
    char *data_ip;
    SOCKADDR_IN data_addr;
    enum mode mode;
} client_t;

//LIST CLIENT
typedef struct my_list_s {
    client_t *client;
    struct my_list_s *next;
} my_list_t;

typedef struct t_t {
    int port;
    char *path;
    int control_socket;
    int new_socket;
    int maxfd;
    SOCKADDR_IN control_addr;
    SOCKADDR_IN client_addr;

    my_list_t *cList;
    char **cmd;

    fd_set readfds;
    fd_set tmpfds;
    fd_set writefds;
} t_t;

//MAIN
void my_help(void);

//SERVER
void my_server(t_t* this);
void init_socket(t_t* this);
void init_fdset(t_t *this);
void server_loop(t_t *this);
void server_send(int clientSocket, char *digitCode, char *msg);

//ERRORS
void socket_error(int control_socket);
void htons_error(t_t *this);
void bind_error(int _bind);
void listen_error(int _listen);
void select_error(int _activity);

//UTILS
int my_strlen(char *str);
char **strtok_wordtab(char *str, char *tok);
int my_strcmp(char *s1, char *s2);

//LINKED LIST
void print_list(my_list_t *list);
my_list_t *create_cell(client_t *client);
my_list_t *add_element(my_list_t *list, client_t *client, int pos);
client_t *get_element(my_list_t *list, int pos);
my_list_t *free_first_element(my_list_t *list);
my_list_t *free_element_at(my_list_t *list, int pos);

//CLIENT
void add_client_to_set(t_t *this);
void handle_new_connection(t_t *this);

//COMMANDS HANDLER
int do_commands(t_t *this, client_t *client);

//COMMANDS
void quit(t_t *this, client_t *client);
void noop(t_t *this, client_t *client);
void user(t_t *this, client_t *client);
void pass(t_t *this, client_t *client);
void pwd(t_t *this, client_t *client);
void pasv(t_t *this, client_t *client);
void help(t_t *this, client_t *client);
void retr(t_t *this, client_t *client);
void stor(t_t *this, client_t *client);
void list(t_t *this, client_t *client);
