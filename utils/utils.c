/*
** EPITECH PROJECT, 2022
** myftp
** File description:
** utils.c
*/

#include "../include/my.h"

int my_is_number(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (1);
    }
    return (0);
}

char *my_strlowcase(char *str)
{
    char *tmp = malloc(sizeof(char) * my_strlen(str) + 1);
    for (int a = 0; str[a] != '\0'; a++) {
        if (str[a] >= 65 && str[a] <= 90) {
            tmp[a] = (str[a] + 32);
            continue;
        }
        tmp[a] = str[a];
    }
    return (tmp);
}

int my_strcasecmp(char *s1, char *s2)
{
    s1 = my_strlowcase(s1);
    s2 = my_strlowcase(s2);
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
    if (str == NULL || my_strcasecmp(str, "\r\n") == 0 || tok == NULL) {
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
