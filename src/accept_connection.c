/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** accept_connection
*/

#include "server.h"

void save_fd(server_t *s)
{
    cli_t *tmp = s->head;
    cli_t *new = (cli_t *)malloc(sizeof(cli_t));

    new->fd = s->c_cli;
    new->user_name = NULL;
    new->password = NULL;
    new->isLog = false;
    if (s->head->next == NULL) {
        s->head->next = new;
        s->head->next->next = (cli_t *)malloc(sizeof(cli_t));
        s->head->next->next = NULL;
    } else {
        for (; tmp->next != NULL; tmp = tmp->next);
        tmp->next = new;
        tmp->next->next = (cli_t *)malloc(sizeof(cli_t));
        tmp->next->next = NULL;
    }
    if (s->c_cli > s->fdMax)
        s->fdMax = s->c_cli;
}

int accept_connection(server_t *s)
{
    socklen_t p_addr_size = sizeof(struct sockaddr_in *);
    if ((s->c_cli = accept(s->sockfd, &s->p_addr, &p_addr_size)) < 0) {
        perror("accept");
        close(s->sockfd);
        exit (84);
    }
    save_fd(s);
    print("220\r\n", s->c_cli);
    return (0);
}

cli_t *get_current(server_t *s)
{
    cli_t *curr = s->head;

    for (; curr != NULL && curr->fd != s->c_cli; curr = curr->next);
    return (curr);
}

void check_fd(server_t *s, int fd)
{
    cli_t *curr;

    if (fd == s->sockfd)
        accept_connection(s);
    else {
        curr = get_current(s);
        s->c_cli = fd;
        handle_client(s, curr);
    }
}