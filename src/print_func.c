/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** print_help
*/

#include "server.h"

void print(const char *msg, int fd)
{
    int len = strlen(msg);

    write(fd, msg, len);
}