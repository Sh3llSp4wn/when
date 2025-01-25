/*
* see main.c for licence
*/
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

// clear the buff incase stat fails so we don't get junk data
#define clean_stat(f, x, r) memset(x, 0, sizeof(struct stat)); \
  r = stat(f, x)

static int get_num_dirents(const char *fname) {
  DIR *head = NULL;
  struct dirent *ent = NULL;
  int ents = 0;  // where have the ent wives gone?

  // check if dir is real,
  // (extemperanious check because
  // of previous stat stuff, but
  // good practice anyway)
  head = opendir(fname);
  if(head == NULL) return -1;
  
  while((ent = readdir(head)) != NULL) {
    ents++;
  }
  closedir(head);
  return ents - 2;
}

// returns 0 if file does not exist
int file_exists(const char *fname, struct stat *statbuf){
  int ret;
  clean_stat(fname, statbuf, ret);
  if(ret) return 0; // failed return 0
  // if ret == 0, then file exists
  return 1;
}

// returns the size of the file
int file_size(const char *fname, struct stat *statbuf){
  int ret;

  // do stat
  clean_stat(fname, statbuf, ret);
  if(ret) return -1; // failed non-existant file has no size

  // intellegently handle file types
  if(S_ISREG(statbuf->st_mode))
    return statbuf->st_size;
  if(S_ISCHR(statbuf->st_mode)
    || S_ISBLK(statbuf->st_mode)
    || S_ISFIFO(statbuf->st_mode)
    || S_ISSOCK(statbuf->st_mode))
  {
    // TODO: make this a useful property
    return 1;
  }
  if(S_ISDIR(statbuf->st_mode))
    return get_num_dirents(fname);
  return -1;
}

void print_fstat(const char *fname) {
  int ret;
  struct stat statbuf;
  clean_stat(fname, &statbuf, ret);
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
