#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

// clear the buff incase stat fails so we don't get junk data
#define clean_stat(f, x, r) memset(&x, 0, sizeof(struct stat)); \
  r = stat(f, &x)

// returns 0 if file does not exist
int file_exists(const char *fname){
  int ret;
  struct stat statbuf;
  clean_stat(fname, statbuf, ret);
  if(ret) return 0; // failed return 0
  // if ret == 0, then file exists
  return 1;
}

// returns the size of the file
int file_size(const char *fname){
  int ret;
  struct stat statbuf;
  clean_stat(fname, statbuf, ret);
  if(ret) return -1; // failed non-existant file has no size
  return statbuf.st_size;
}

void print_fstat(const char *fname) {
  int ret;
  struct stat statbuf;
  clean_stat(fname, statbuf, ret);
  if(ret) return; // failed don't print

  printf("dev     = %lu\n", statbuf.st_dev     );
  printf("ino     = %lu\n", statbuf.st_ino     );
  printf("mode    = %u\n",  statbuf.st_mode    );
  printf("nlink   = %lu\n", statbuf.st_nlink   );
  printf("uid     = %u\n",  statbuf.st_uid     );
  printf("gid     = %u\n",  statbuf.st_gid     );
  printf("rdev    = %lu\n", statbuf.st_rdev    );
  printf("blksize = %ld\n", statbuf.st_blksize );
  printf("blocks  = %ld\n", statbuf.st_blocks  );
}
