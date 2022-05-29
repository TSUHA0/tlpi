//
// Created by tsuhao on 2022/5/27.
//

//#define _FILE_OFFSET_BITS 64
#include <fcntl.h>
#include "tlpi_hdr.h"


int main(int argc, const char *argv[]) {
    if (argc != 3) usageErr("%s write-content offset", argv[1]);
    int fd = open(argv[1], O_CREAT | O_WRONLY, 0666);
    if (fd == -1) errExit("open");

    off_t offset = getLong(argv[2], GN_ANY_BASE, argv[2]);
    printf("%lu", sizeof offset);
    if (offset < 0) errExit("offset");

    if (lseek(fd, offset, SEEK_SET) == -1) errExit("lseek");
    if (write(fd, "test", 4) == -1) errExit("write");

    exit(EXIT_SUCCESS);
}