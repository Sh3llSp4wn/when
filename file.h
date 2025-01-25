/*
* see when.c for licence
*/
#ifndef WHEN_FILE_H
#define WHEN_FILE_H
#include <sys/stat.h>

int file_exists(const char *fname, struct stat *statbuf);
int file_size(const char *fname, struct stat *statbuf);
void print_fstat(const char *fname);
#endif
