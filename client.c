#include "libs.h"

int main(int argc, char **argv) {
    int ppid = getppid();

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

    if(strcmp("find", argv[1]) == 0) {
        int b_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (b_sock_fd < 0) {
            printf("Can't create socket\n");
            return -1;
        }

        int yes = 1;
        int res = setsockopt(b_sock_fd, SOL_SOCKET, SO_BROADCAST, (char *) &yes, sizeof(yes));
        if (res == -1) {
            perror("Setsockopt error\n");
            exit(-1);
        }

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        res = setsockopt(b_sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        if (res == -1) {
            perror("Setsockopt error\n");
            exit(-1);
        }

        struct sockaddr_in b_sock_addr;
        int b_addr_len = sizeof(struct sockaddr_in);

        memset((void *) &b_sock_addr, 0, b_addr_len);
        b_sock_addr.sin_family = AF_INET;
        b_sock_addr.sin_port = htons(B_PORT); //!!!!
        b_sock_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

        char *b_buf = calloc(MAX_MESSAGE_SIZE, 1);
        strcpy(b_buf, "Is anybody here?");


        int b_sent = sendto(b_sock_fd, "Is anybody here?", strlen("Is anybody here?"), 0,
                            (const struct sockaddr *) &b_sock_addr, b_addr_len);
        if (b_sent < 0) {
            perror("Error while sending (broadcast)\n");
            return -1;
        }

        while (1) {
            struct sockaddr_in b_rec_addr;
            char *rec_buf = calloc(MAX_MESSAGE_SIZE, 1);
            int b_addr_size = sizeof(b_rec_addr);
            int b;
            b = recvfrom(b_sock_fd, rec_buf, MAX_MESSAGE_SIZE, 0, (struct sockaddr *restrict) &b_rec_addr,
                         (socklen_t *restrict) &b_addr_size);
            if (b < 0) {
                //perror("Can't read message\n");
                exit(0);
            }
            printf("Server found: %s\n", to_addr(&b_rec_addr));
        }
    }


    char *buf = calloc(MAX_MESSAGE_SIZE, 1);
    sprintf(buf, "%05d", ppid);
    strcat(buf, argv[1]);
    if(argv[2]) {
        strcat(buf, " ");
        strcat(buf, argv[2]);
    }

    int sent = sendto(sock_fd, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(sent < 0) {
        printf("Error while sending\n");
        return -1;
    }

    close(sock_fd);
    return 0;
}