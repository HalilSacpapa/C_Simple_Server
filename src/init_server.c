/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** init_server
*/

#include "server.h"

void select_fd(server_t *s)
{
    for (int fd = 0; fd <= s->fdMax; fd++)
        if (FD_ISSET(fd, &s->rfds))
            check_fd(s, fd);
}

void set_select(server_t *s)
{
    cli_t *tmp = s->head;

    FD_ZERO(&s->rfds);
    if (s->head != NULL)
        FD_SET(s->head->fd, &s->rfds);
    for (; tmp != NULL; tmp = tmp->next)
        FD_SET(tmp->fd, &s->rfds);
    FD_SET(s->sockfd, &s->rfds);
}

int server_loop(server_t *s)
{
    for (int ret = 0; 42; ret = 0) {
        set_select(s);
        ret = select(s->fdMax + 1, &s->rfds, NULL, NULL, &s->tv);
        if (ret < 0) {
            perror("select");
            return (84);
        }
        select_fd(s);
    }
    return (0);
}

void set_values(server_t *s)
{
    cli_t *tmp = (cli_t *)malloc(sizeof(cli_t));

    tmp->fd = s->sockfd;
    s->head = tmp;
    s->head->next = (cli_t *)malloc(sizeof(cli_t));
    s->head->next = NULL;
    s->fdMax = s->sockfd;
    s->tv.tv_sec = 0;
    s->tv.tv_usec = 550001;
}

int launch_server(server_t *s)
{
    if ((s->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        return (84);
    }
    s->addr.sin_family = AF_INET;
    s->addr.sin_port = htons(s->port);
    s->addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(s->sockfd, (struct sockaddr *)&s->addr,
        sizeof(struct sockaddr_in)) == -1) {
        perror("bind");
        close(s->sockfd);
        return (84);
    }
    if (listen(s->sockfd, 30) == -1) {
        perror("listen");
        return (84);
    }
    set_values(s);
    return (server_loop(s));
}