#ifndef WHEN_FILE_H
#define WHEN_FILE_H

int file_exists(const char *fname);
int file_size(const char *fname);
void print_fstat(const char *fname);
#endif
