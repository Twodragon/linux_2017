//
// Created by Сергей Ефимочкин on 10.05.2018.
//
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <netinet/in.h>

#include "Network_utils.h"
#include "Client.h"

#define NAME_SIZE 32
#define COMMAND_SIZE 32
#define FIRST_ARG_SIZE 128
#define SECOND_ARG_SIZE 1024
#define INPUT_SIZE 1186

void Client_run() {
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8901);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    connect(sock, (struct sockaddr *) &addr, sizeof(addr));

    char name[NAME_SIZE];
    printf("Print the name of wanted database\n");
    fgets(name, NAME_SIZE, stdin);
    send_answer(sock, name);


    char command[COMMAND_SIZE + 1]; // +1 for terminating symbol
    char first_argument[FIRST_ARG_SIZE + 1];
    char second_argument[SECOND_ARG_SIZE + 1];
    char input_line[INPUT_SIZE + 1];


    while(fgets(input_line, INPUT_SIZE, stdin) != 0){
        send(sock, input_line, INPUT_SIZE, 0);
        safe_parse_input(sock, input_line, COMMAND_SIZE, FIRST_ARG_SIZE, SECOND_ARG_SIZE,
                         command, first_argument, second_argument);

        char *answer = get_answer(sock);
        if (strlen(answer) > 0)
            printf("%s\n", answer);
        free(answer);

        if (strcmp(command, "exit") == 0)
            break;
        else if (strcmp(command, "stop") == 0)
                break;
    }
    close(sock);

}