//
// Created by tsuhao on 2022/5/26.
//

#include <fcntl.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

#define BUFF_SIZE 1024
char buf[BUFF_SIZE] = {0};

int main(int argc, const char *argv[]) {
    if (argc != 3)
        usageErr("%s old-file new-file", argv[0]);

    int inputFD = open(argv[1], O_RDONLY);
    if (inputFD == -1)
        errExit("err read %s", argv[1]);
    int openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int outputFd = open(argv[2], openFlags, filePerm);
    if (outputFd == -1)
        errExit("err read %s", argv[2]);
    ssize_t numRead;

    while ((numRead = read(inputFD, buf, BUFF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead)
            fatal("couldn't write whole buffer");
    }

   if (numRead == -1)
       errExit("read");
   if (close(inputFD) == -1)
       errExit("close input");
    if (close(outputFd) == -1)
        errExit("close output");

    exit(EXIT_SUCCESS);
}