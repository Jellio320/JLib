#define JLIB_IO
#include "Jlinternal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

ullong jlfcharcount(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("jlfcharcount: ");
        return 0;
    }
    size_t count = 0;
    while (fgetc(file) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

ullong jlfcharcountf(FILE* file) {
    long l;
    size_t count = 0;
    if ((l = ftell(file)) == -1) {
        perror("jlfcharcountf: ");
        return 0;
    }
    fseek(file, 0, SEEK_SET);
    while (fgetc(file) != EOF) {
        count++;
    }
    if (fseek(file, l, SEEK_SET) == -1) {
        perror("jlfcharcountf: ");
        return 0;
    }
    return count;
}

void jlparsefile(char* dest, const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not find file %s!!!\n", path);
        return;
    }
    char c;
    while ((c = fgetc(file)) != EOF) {
        *dest++ = c;
    }
    fclose(file);
}

void jlparsefilen(char* dest, const char* path, size_t n) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not find file %s!!!\n", path);
        return;
    }
    char c;
    while (((c = fgetc(file)) != EOF) && n--) {
        *dest++ = c;
    }

    fclose(file);
}

void jlparsefilef(char* dest, FILE* file) {
    long l;
    if ((l = ftell(file)) == -1) {
        perror("jlparsefilef: ");
        *dest = 0;
        return;
    }
    fseek(file, 0, SEEK_SET);
    char c;
    while ((c = fgetc(file)) != EOF) {
        *dest++ = c;
    }
    if (fseek(file, l, SEEK_SET) == -1) {
        perror("jlparsefilef");
        return;
    }
}

void jlparsefilefn(char* dest, FILE* file, size_t n) {
    long l;
    if ((l = ftell(file)) == -1) {
        perror("jlparsefilef: ");
        *dest = 0;
        return;
    }
    fseek(file, 0, SEEK_SET);
    char c;
    while (((c = fgetc(file)) != EOF) && n--) {
        *dest++ = c;
    }
    if (fseek(file, l, SEEK_SET) == -1) {
        perror("jlparsefilef");
        return;
    }
}

void jlstrinv(char* src, char* dest) {
    assert(src);
    size_t len = strlen(src);
    if (src == dest) {
        char buffer;
        for (dest += len - 1; src < dest; src++) {
            buffer = *src;
            *src = *dest;
            *dest-- = buffer;
        }
    } else {
        for (long long i = len - 1; i > -1; i--) {
            *dest++ = *(src + i);
        }
        *dest = 0;
    }
}

void jlfliparrayls(void* arr, unsigned long long length,
    unsigned long long stride) {
    assert(arr);
    struct TypeSize {
        uchar byte[stride];
    } buffer, *start, *end;

    start = (struct TypeSize*) arr;
    for (end = start + ((length / stride) - 1); start < end; start++) {
        buffer = *start;
        *start = *end;
        *end-- = buffer;
    }
}