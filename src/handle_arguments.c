/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** handle_arguments
*/

#include "server.h"

void usage(void)
{
    printf("Usage:\t./server [port] [path]\n\t");
    printf("Use [./client [ip adress] [port]] to connect to the server");
    printf("\n\ttype '-h' to see this help.\n");
    exit (0);
}

void parse_args(int ac, char **av, server_t *s)
{
    if (ac == 2 && !strcmp(av[1], "-h"))
        usage();
    else if (ac != 3) {
        print("You must provide a port and a path. ", 2);
        print("Type '-h' for usage.\n", 2);
        exit (84);
    }
    for (int i = 0; av[1][i]; i++)
        if (av[1][i] < '0' || av[1][i] > '9') {
            print("You must provide a valid port. ", 2);
            print("Type '-h' for usage.\n", 2);
            exit(84);
        }
    if ((s->path = chdir(av[2])) == -1) {
        print("You must provide a valid path. ", 2);
        print("Type '-h' for usage.\n", 2);
        exit(84);
    }
}