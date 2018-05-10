//
// Created by Сергей Ефимочкин on 10.05.2018.
//
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Network_utils.h"

void send_answer(int sock, char* answer){
    char buf[16];
    memset(buf, 0, 16);
    sprintf(buf, "%i", strlen(answer));
    send(sock, buf, 16, 0);
    send(sock, answer, strlen(answer), 0);
}

char* get_answer(int sock){
    char buf[16];
    memset(buf, 0, 16);
    recv(sock, buf, 16, 0);
    int size_of_answer;
    sscanf(buf, "%i", &size_of_answer);

    char *answer = malloc(sizeof(char) * (size_of_answer + 1));
    memset(answer, 0, (size_of_answer + 1));

    recv(sock, answer, (size_t)size_of_answer, 0);
    return answer;
}
