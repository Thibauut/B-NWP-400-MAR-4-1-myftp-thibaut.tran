/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** utils.c
*/

#include "../include/my.h"

int my_strcmp(char *s1, char *s2)
{
    int len = my_strlen(s2);
    if (len != my_strlen(s1))
        return (1);
    for (int j = 0; j != len; j += 1) {
        if (s1[j] != s2[j])
            return (1);
    }
    return (0);
}

int my_strlen(char *str)
{
    int i = 0;
    for (; str[i]; i += 1);
    return i;
}

char **strtok_wordtab(char *str, char *tok)
{
    if (str == NULL || my_strcmp(str, "\r\n") == 0 || tok == NULL) {
        char **tmp = malloc(sizeof(char *) * 1);
        tmp[0] = strdup("\r\n");
        return (tmp);
    }
    char **tab = malloc(sizeof(char *) * 4096);
    char *tmp = strtok(str, tok);
    int i = 0;
    for (; tmp != NULL; i++) {
        tab[i] = strdup(tmp);
        tmp = strtok(NULL, tok);
    }
    tab[i] = NULL;
    return (tab);
}
