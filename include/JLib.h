#ifndef JLIB_H_
#define JLIB_H_

#include <stdio.h>

#ifndef JLIB
#define JLIB extern
#endif

#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifndef UNUSED
#define UNUSED(x) ((void) (x))
#endif

typedef long long llong;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;

JLIB unsigned long long jlfcharcount(const char* path);
JLIB unsigned long long jlfcharcountf(FILE* file);
JLIB void jlparsefile(char* dest, const char* path);
JLIB void jlparsefilen(char* dest, const char* path, size_t n);
JLIB void jlparsefilefn(char* dest, FILE* file, size_t n);
JLIB void jlparsefilef(char* dest, FILE* file);
JLIB void jlstrinv(char* src, char* dest);
JLIB void jlfliparrayls(void* arr, unsigned long long length,
    unsigned long long stride);
#define jlfliparray(arr) jlfliparrayls(arr, sizeof(arr), sizeof *arr)

#undef JLIB

#endif //JLIB_H_