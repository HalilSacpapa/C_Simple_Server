/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** handle_client
*/

#include "server.h"

void remove_next_fd(cli_t *del, cli_t *tmp, int fd)
{
    while (tmp->next != NULL) {
        if (tmp->next->fd == fd) {
            del = tmp->next;
            tmp->next = tmp->next->next;
            free(del);
            return;
        } else
            tmp = tmp->next;
    }
}

void remove_second_fd(cli_t *del, cli_t *tmp)
{
    del = tmp->next;
    tmp->next = (cli_t *)malloc(sizeof(cli_t));
    tmp->next = NULL;
    free(del);
}

int check_first_fd(cli_t *del, cli_t *tmp, server_t *s)
{
    if (tmp->fd == s->c_cli && tmp->next == NULL) {
        free(tmp);
        return (1);
    } else if (tmp->fd == s->c_cli) {
        del = tmp;
        s->head = s->head->next;
        free(del);
        return (1);
    }
    return (0);
}

void kick_client(server_t *s)
{
    cli_t *del = (cli_t *)malloc(sizeof(cli_t));
    cli_t *tmp = s->head;
    int id = 0;

    if (check_first_fd(del, tmp, s) == 1)
        close(s->c_cli);
    else if (tmp->next && tmp->next->fd == s->c_cli && tmp->next->next == NULL)
        remove_second_fd(del, tmp);
    else
        remove_next_fd(del, tmp, s->c_cli);
    close(s->c_cli);
    if (s->c_cli == s->fdMax)
        for (cli_t *tmp = s->head; tmp != NULL; tmp = tmp->next)
            if (id < tmp->fd)
                id = tmp->fd;
    s->fdMax = id;
    print("221\r\n", s->c_cli);
}

void handle_client(server_t *s, cli_t *curr)
{
    char *input = NULL;
    size_t len;
    FILE *strm = fdopen(s->c_cli, "rw");

    getline(&input, &len, strm);
    str_to_word_tab(curr, input);
    free(input);
    if (!strncmp(curr->parsed_input[0], "QUIT", 4))
        kick_client(s);
    else
        check_cmd(curr);
    free(curr->parsed_input);
}