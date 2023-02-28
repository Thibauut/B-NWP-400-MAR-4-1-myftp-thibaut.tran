/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** ultils_link_list2.c
*/

#include "../include/my.h"

my_list_t *free_first_element(my_list_t *list)
{
    if (list == NULL)
        return (NULL);
    my_list_t *tmp = list;
    list = tmp->next;
    return (list);
}
