/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-thibaut.tran
** File description:
** utils2
*/

#include "../include/my.h"

char *my_strcat(char *dest, char *src)
{
    int a = 0, i = 0;
    char *tmp = malloc(sizeof(char) *
    ((my_strlen(dest) + my_strlen(src)) + 1));
    for (; dest[a] != '\0'; a += 1)
        tmp[a] = dest[a];
    for (; src[i] != '\0'; i += 1)
        tmp[a + i] = src [i];
    tmp[a + i] = '\0';
    return (tmp);
}
