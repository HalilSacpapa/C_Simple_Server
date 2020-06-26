/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** handle_command
*/

#include "server.h"

int check_status_pass(cli_t *curr)
{
    if (curr->user_name && !strncmp(curr->user_name, "Anonymous", 9))
        if (curr->password && !strncmp(curr->password, " ", 1)) {
            print("230\r\n", curr->fd);
            curr->isLog = true;
            return (1);
        }
    if (curr->password && !strncmp(curr->password, " ", 1))
        print("332\r\n", curr->fd);
    if (curr->password && strncmp(curr->password, " ", 1))
        print("332\r\n", curr->fd);
    return (1);
}

int check_status_user(cli_t *curr)
{
    if (curr->user_name && !strncmp(curr->user_name, "Anonymous", 9))
        if (curr->password && !strncmp(curr->password, " ", 1)) {
            print("230\r\n", curr->fd);
            curr->isLog = true;
            return (1);
        }
    if (curr->user_name && !strncmp(curr->user_name, "Anonymous", 9))
        print("331\r\n", curr->fd);
    if (curr->user_name && strncmp(curr->user_name, "Anonymous", 9))
        print("332\r\n", curr->fd);
    return (1);
}

int log_in(cli_t *curr)
{
    int ret = 0;
    int len = 0;

    if (curr->parsed_input[1] && !strncmp("USER", curr->parsed_input[0], 4)) {
        len = (strlen(curr->parsed_input[1]) + 1);
        curr->user_name = malloc(sizeof(char) * len);
        strcpy(curr->user_name, curr->parsed_input[1]);
        ret = check_status_user(curr);
    }
    if (!strncmp("PASS", curr->parsed_input[0], 4)) {
        if (curr->parsed_input[1] == NULL) {
            curr->password = malloc(sizeof(char) * 2);
            strcpy(curr->password, " ");
        } else {
            len = (strlen(curr->parsed_input[1]) + 1);
            curr->password = malloc(sizeof(char) * len);
            strcpy(curr->password, curr->parsed_input[1]);
        }
        ret = check_status_pass(curr);
    }
    return (ret);
}

void check_cmd(cli_t *curr)
{
    if (curr->isLog == false) {
        if (log_in(curr) == 1)
            return;
        else
            print("332\r\n", curr->fd);
    } else if (curr->isLog == true)
        treat_cmd(curr);
}