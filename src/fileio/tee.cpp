//
// Created by tsuhao on 2022/5/27.
//

#include <fcntl.h>
#include "tlpi_hdr.h"

#define BUFSIZE 1024
char buf[BUFSIZE + 1];

int main(int argc, const char *argv[]) {
    if (argc != 1 && argc != 3) usageErr("%s [-a append-file]", argv[0]);
    ssize_t numRead;

    while ((numRead = read(STDIN_FILENO, buf, BUFSIZE)) > 0) {
        if (argc == 3 && strcmp("-a", argv[1]) == 0) {
            int fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (write(fd, buf, BUFSIZE) < 0)
                errExit("write");
            if (numRead == -1) errExit("read");
        }
        printf("%s", buf);
    }
    if (numRead == -1) errExit("read");

    errExit(EXIT_SUCCESS);
}