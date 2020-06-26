/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <stdbool.h>
#include <time.h>

#ifndef SERVER_H_
#define SERVER_H_

typedef struct clients {
    int fd;
    char *user_name;
    char *password;
    bool isLog;
    char **parsed_input;
    struct clients *next;
} cli_t;

typedef struct server_s {
    int port;
    int path;
    int sockfd;
    struct sockaddr_in addr;
    struct sockaddr p_addr;
    struct timeval tv;
    fd_set rfds;
    cli_t *head;
    int fdMax;
    int c_cli;
} server_t;

// main.c
int main(int ac, char **av);

// handle_arguments.c
void parse_args(int ac, char **av, server_t *s);

// print_func.c
void print(const char *msg, int fd);

// init_server.c
int launch_server(server_t *s);

// accept_connection.c
void check_fd(server_t *s, int fd);

// handle_client.c
void kick_client(server_t *s);
void handle_client(server_t *s, cli_t *curr);

// str_to_word_tab.c
void str_to_word_tab(cli_t *curr, char *input);

// handle_command.c
void check_cmd(cli_t *curr);

// treat_command.c
void treat_cmd(cli_t *curr);

#endif /* !SERVER_H_ */
