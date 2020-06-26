/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "server.h"

int main(int ac, char **av)
{
    server_t s;

    parse_args(ac, av, &s);
    s.port = atoi(av[1]);
    if (s.port < 1 || s.port > 65535) {
        write(2, "Invalid port\n", 14);
        return (84);
    }
    s.head = (cli_t *)malloc(sizeof(cli_t));
    s.head = NULL;
    if (launch_server(&s) == 84) {
        close(s.sockfd);
        return (84);
    }
    return (0);
}