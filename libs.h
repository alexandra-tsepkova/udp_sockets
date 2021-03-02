#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define PORT 65535
#define MAX_MESSAGE_SIZE 1024
#define TABLE_SIZE 100
#define DEFAULT_PATH "/"
#define MAX_THREADS 5
#define PPID_SIZE 5