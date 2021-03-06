#define _GNU_SOURCE
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {

    int fds[2];
    int err = socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
    if (err != 0) {
        error(1, errno, "couldn't create socket pair");
    }

    int optval = 1;
    err = setsockopt(fds[0], SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));
    if (err != 0) {
        error(1, errno, "couldn't set socket options");
    }

    pid_t pid = fork();
    if (pid == 0) {
        dup2(fds[1], 1);
        dup2(fds[1], 2);
        close(fds[0]);
        close(fds[1]);
        execvp(argv[1], argv + 1);
        error(1, errno, "couldn't exec");
    }
    close(fds[1]);

    struct msghdr msg = {0};

    struct iovec buf_iov[1];

    char buf[4096];
    buf_iov[0].iov_base = buf;
    buf_iov[0].iov_len = sizeof(buf);

    msg.msg_iov = buf_iov;
    msg.msg_iovlen = 1;

    char ctrl[4096];
    msg.msg_control = ctrl;
    msg.msg_controllen = sizeof(ctrl);

    struct ucred* ucred;
    char pid_string[1024];
    int pid_len;

    ssize_t recv;

    while ((recv = recvmsg(fds[0], &msg, 0)) > 0) {
        struct cmsghdr* cmsg;
        for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
            if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_CREDENTIALS) {
                ucred = (struct ucred*)CMSG_DATA(cmsg);
                pid_len = snprintf(pid_string, sizeof(pid_string), "%d", ucred->pid);
            }
        }
#ifndef CDBM_FORMAT
        char* nl;
        char* line = buf;
        while ((nl = memchr(line, '\n', buf + recv - line))) {
            printf("(%.*s) %.*s\n", pid_len, pid_string, (int)(nl - line), line);
            line = nl + 1;
        }
        if (line < buf + recv) {
            printf("(%.*s)\\%.*s\n", pid_len, pid_string, (int)(buf + recv - line), line);
        }
#else
        printf("+%d,%d:%.*s->%.*s\n", pid_len, (int)recv, pid_len, pid_string, (int)recv, buf);
#endif
    }
    if (recv == -1)
        error(1, errno, "io error");
    printf("\n");
    exit(0);
}
