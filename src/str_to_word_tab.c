/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** str_to_word_tab
*/

#include "server.h"

int count_occurs(char *str, char c)
{
    int cnt = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            cnt++;
    return (cnt);
}

void str_to_word_tab(cli_t *curr, char *input)
{
    int len = count_occurs(input, ' ');
    int u = 0;
    int y = 0;

    if (len == 0) {
        curr->parsed_input = malloc(sizeof(char *) * 2);
        curr->parsed_input[0] = malloc(sizeof(char) * strlen(input));
        strncpy(curr->parsed_input[0], input, (strlen(input) - 1));
        curr->parsed_input[1] = NULL;
        return;
    }
    curr->parsed_input = malloc(sizeof(char *) * len);
    for (int i = 0; input[i]; i++) {
        curr->parsed_input[u] = malloc(sizeof(char) * strlen(input));
        for (; input[i] != ' ' && input[i] != '\r' && input[i]; y++, i++)
            curr->parsed_input[u][y] = input[i];
        curr->parsed_input[u][y] = '\0';
        y = 0;
        u++;
    }
    curr->parsed_input[u] = NULL;
}