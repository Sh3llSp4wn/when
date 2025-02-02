/*
* see when.c for licence
*/
#ifndef WHEN_FILE_H
#define WHEN_FILE_H
#include <sys/stat.h>

/*
 * 0 on dne and 1 if file exists
 */
int file_exists(const char *fname, struct stat *statbuf);
/*
 * return the file size as aquired by stat
 * OR
 * some useful analogue for file size (items in dir, for example)
 */
int file_size(const char *fname, struct stat *statbuf);
/*
 * development function
 */
void print_fstat(const char *fname);
#endif
