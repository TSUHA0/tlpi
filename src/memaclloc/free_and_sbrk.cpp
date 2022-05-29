//
// Created by tsuhao on 2022/5/29.
//
#include "tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, const char *argv[]) {
    char *ptr[MAX_ALLOCS];

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
    int numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");
    if (numAllocs > MAX_ALLOCS)
        cmdLineErr("num-allocs > %d\n", MAX_ALLOCS);
    int blockSize = getInt(argv[2], GN_GT_0, "block-size");

    int freeStep = argc > 3 ? getInt(argv[3], GN_GT_0, "step") : 1;
    int freeMin = argc > 4 ? getInt(argv[4], GN_GT_0, "min") : 1;
    int freeMax = argc > 5 ? getInt(argv[5], GN_GT_0, "max") : numAllocs;

    if (freeMax > numAllocs)
        cmdLineErr("free-max > num-allocs\n");
    printf("Initial program break:  %10p\n", sbrk(0));
    printf("Allocating %d*%d bytes \n", numAllocs, blockSize);
    for (int j = 0; j < numAllocs; ++j) {
        ptr[j] = (char *)malloc(blockSize);
        if (ptr[j] == nullptr) errExit("malloc");
    }
    printf("Program break is now:   %10p\n", sbrk(0));
    printf("Freeing blocks from %d to %d, in steps of %d\n", freeMin, freeMax, freeStep);
    for (int j = freeMin - 1; j < freeMax; j += freeStep) {
        free(ptr[j]);
    }
    printf("After free(), break is: %10p\n", sbrk(0));
    exit(EXIT_SUCCESS);
}