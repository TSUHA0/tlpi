//
// Created by tsuhao on 2022/5/27.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"


int main(int argc, const char *argv[]) {
    if (argc < 3)
        usageErr("%s file {r<length>|w<string>|s<offset>}...\n", argv[0]);
    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    if (fd == -1)
        errExit("open failed");

    for (int ap = 2; ap < argc; ++ap) {
        switch (argv[ap][0]) {
            case 'r':
            case 'R': {
                long len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                char *buf = new char[len];
                int numRead = read(fd, buf, len);
                if (numRead == -1) errExit("read", argv[ap]);
                else if (numRead == 0) printf("%s: read EOF\n", argv[ap]);
                else {
                    printf("%s: ", argv[ap]);
                    for (int i = 0; i < len; ++i) {
                        if (argv[ap][0] == 'r')
                            printf("%c", isprint((unsigned char) buf[i]) ? buf[i] : '?');
                        else printf("%02x ", (unsigned char) buf[i]);
                    }
                    printf("\n");
                }
                delete[]buf;
                break;
            }
            case 'w': {
                ssize_t numWrite = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if (numWrite == -1) errExit("write");
                printf("%s: write %ld bytes\n", argv[ap], numWrite);
                break;
            }
            case 's': {
                off_t offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                if (lseek(fd, offset, SEEK_SET) == -1) errExit("lseek");
                printf("%s: seek success\n", argv[ap]);
                break;
            }
            default:
                cmdLineErr("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }
    exit(EXIT_SUCCESS);
}