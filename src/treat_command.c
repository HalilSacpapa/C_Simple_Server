/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** treat_command
*/

#include "server.h"

void treat_cmd5(cli_t *curr)
{
    if (!strncmp(curr->parsed_input[0], "NOOP", 4))
        print("200\r\n", curr->fd);
    else {
        if (!strncmp(curr->parsed_input[0], "USER", 4))
            print("230\r\n", curr->fd);
        else if (!strncmp(curr->parsed_input[0], "PASS", 4))
            print("230\r\n", curr->fd);
        else
            print("404\r\n", curr->fd);
    }
}

void treat_cmd4(cli_t *curr)
{
    if (!strncmp(curr->parsed_input[0], "PWD", 3))
        print("257\r\n", curr->fd);
    else if (!strncmp(curr->parsed_input[0], "HELP", 4))
        print("214\r\n", curr->fd);
    else
        treat_cmd5(curr);
}

void treat_cmd3(cli_t *curr)
{
    if (!strncmp(curr->parsed_input[0], "LIST", 4))
        print("150\r\n", curr->fd);
    else if (!strncmp(curr->parsed_input[0], "DELE", 4))
        print("250\r\n", curr->fd);
    else
        treat_cmd4(curr);
}

void treat_cmd2(cli_t *curr)
{
    if (!strncmp(curr->parsed_input[0], "STOR", 4))
        print("150\r\n", curr->fd);
    else if (!strncmp(curr->parsed_input[0], "RETR", 4))
        print("150\r\n", curr->fd);
    else
        treat_cmd3(curr);
}

void treat_cmd1(cli_t *curr)
{
    if (!strncmp(curr->parsed_input[0], "PORT", 4))
        print("200\r\n", curr->fd);
    else if (!strncmp(curr->parsed_input[0], "PASV", 4))
        print("227\r\n", curr->fd);
    else
        treat_cmd2(curr);
}

void treat_cmd(cli_t *curr)
{
    if (!strncmp(curr->parsed_input[0], "CWD", 3))
        print("250\r\n", curr->fd);
    else if (!strncmp(curr->parsed_input[0], "CDUP", 4))
        print("200\r\n", curr->fd);
    else
        treat_cmd1(curr);
}
