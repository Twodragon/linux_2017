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

void Client_run() {
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    connect(sock, (struct sockaddr *) &addr, sizeof(addr));

    char name[32];
    memset(name, 0, 32);
    printf("Print the name of wanted database\n");
    fgets(name, 32, stdin);
    send_answer(sock, name);


    char command[32];
    char first_argument[128];
    char second_argument[1024];
    char input_line[1184];
    memset(command, 0, 32);
    memset(first_argument, 0, 128);
    memset(second_argument, 0, 1024);
    memset(input_line, 0, 1184);


    while(fgets(input_line, 1184, stdin) != 0){
        send(sock, input_line, 1184, 0);
        sscanf(input_line, "%s %s %s", command, first_argument, second_argument);

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