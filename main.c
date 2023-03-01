/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** main.C
*/

#include "include/my.h"

void my_help(void)
{
    printf("%s\n%s\n%s%s\n", h1, h2, h3, h4);
}

void init_all(t_t *this, char **av)
{
    this->port = atoi(av[1]);
    this->path = strdup(av[2]);
    if (chdir(this->path) == -1) {
        printf("Error: %s\n", strerror(errno));
        exit(84);
    }
    this->cList = NULL;
}

int main(int ac, char **av)
{
    t_t *this = malloc(sizeof(t_t));
    if (ac == 1)
        return (84);
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == 'e'
    && av[1][3] == 'l' && av[1][4] == 'p') {
        my_help();
        return (0);
    }
    if (ac != 3)
        return (84);
    init_all(this, av);
    my_server(this);
    return (0);
}
