#include "libs.h"

int main(int argc, char **argv) {
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        printf("Can't create socket");
        return -1;
    }

    const struct sockaddr_in server_addr = {AF_INET, htons(PORT), inet_addr("127.0.0.1")};

    if(argc < 2) {
        printf("Not enough arguments\n");
        return -1;
    }

    char *buf = calloc(MAX_MESSAGE_SIZE, 1);
    strcpy(buf, argv[1]);
    if(argv[2]) {
        strcat(buf, " ");
        strcat(buf, argv[2]);
    }
    int sent = sendto(sock_fd, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(sent < 0) {
        printf("Error while sending\n");
        return -1;
    }









//    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
//    {
//        printf("Connection error\n");
//        return -1;
//    }
//
//
//    if(strcmp(argv[1], "PRINT") == 0) {
//        if(argc < 3) {
//            printf("No message!\n");
//            return -1;
//        }
//        char *buf = calloc(strlen(argv[2]) + 1, 1);
//        buf[0] = '1';
//        strcat(buf, argv[2]);
//        if(write(sock_fd, buf, strlen(buf))< 0) {
//            printf("Can't write message");
//            return -1;
//        }
//        free(buf);
//    }
//
//    if(strcmp(argv[1],"EXIT") == 0) {
//        char buf[1];
//        buf[0] = '0';
//        write(sock_fd, buf, 1);
//    }

    close(sock_fd);
    return 0;



}