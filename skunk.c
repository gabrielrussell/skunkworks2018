#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    int fds[2];
    int err = pipe(fds);
    pid_t pid = fork();
    if (pid == 0) {
        close(fds[0]);
        dup2(fds[1],1);
        printf("hello world\n");
        exit(0);
    }
    close(fds[1]);
    dup2(fds[0],0);
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
   
    read = getline(&line,&len,stdin);
    printf("%s",line);
    exit(0);
}
