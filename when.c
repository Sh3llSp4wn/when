// mine
#include "when.h"
#include "file.h"
// std library
#include <time.h>
#include <stdio.h>

enum CheckCodes{
  CONDITION_UNMET,
  CONDITION_MET
};

// code clarity for later
#define UNSIZED_FILE_TYPES(x) (S_ISCHR(x) | S_ISBLK(x) | S_ISFIFO(x) | S_ISSOCK(x))

static int do_check(settings_s *settings) {
  // handle file parameters
  static int  has_printed_warning = 0;

  struct stat statbuf;
  int         file_sz     = 0;
  int         file_extant = file_exists(settings->path, &statbuf);

  // set default conditon to be unmet
  int condition = CONDITION_UNMET;
  // if watch delete and file dne, met
  if(settings->w_del && !file_extant)
    condition = CONDITION_MET;
  // if watch create and file exists, met
  if(settings->w_creat && file_extant)
    condition = CONDITION_MET;
  if(file_extant) {
    // get the file size
    file_sz = file_size(settings->path, &statbuf);
    // do a quick check to see if the file is 
    // of a type that doesn't have a meaningful
    // concept of size, or more specifically a size
    // that changes
    //
    // Print a warning instead of treating this as fatal.
    if(settings->verbose) {
      if(UNSIZED_FILE_TYPES(statbuf.st_mode)){
        if(!has_printed_warning) {
          fprintf(stderr, "You appear to have selected a size option (-z, -s) on an unsized file type, this is likely invalid\n");
          // don't repeat warnings
          has_printed_warning++;
        }
      }
    }
    // if watch zero and file len == 0, met
    if(settings->w_zero && (file_sz == 0))
      condition = CONDITION_MET;
    // if watch size and file len >= size, met
    if(settings->w_size && (file_sz >= settings->w_size))
      condition = CONDITION_MET;
  }

  // if negate, then negate the condition
  if(settings->negate) condition = !condition;

  return condition;
}

#define ns 1
#define us 1000 * ns
#define ms 1000 * us

static void do_sleep(settings_s *settings) {
  // if cycle_length is default value -1, then sleep default
  // otherwise sleep the specified amount of time
  int             seconds  = 0;
  int             useconds = 0;
  struct timespec wait_for;

  if(settings->cycle_length == -1) {
    // default to 250 ms
    wait_for.tv_sec  = 0;
    wait_for.tv_nsec = (250 * ms);
  } else {
    // convert to seconds and ms for use with nanosleep
    seconds  = settings->cycle_length / 1000;
    useconds = settings->cycle_length % 1000;
    wait_for.tv_sec  = seconds;
    wait_for.tv_nsec = (useconds * ms);
  }
  // no use for the remainder parameter
  // because we are not handling signals
  nanosleep(&wait_for, NULL);
}

int when(settings_s *settings) {
  int cycles = 0;
  int ret    = CONDITION_UNMET;

  if(settings->verbose) {
    fprintf(stderr, "Watching \"%s\"\n", settings->path);
  }

  // while do_check returns unmet, keep checking
  while((ret = do_check(settings)) == CONDITION_UNMET) {
    // if we run out of cycles, break
    if ((cycles++ > settings->number_of_cycles)
      && (settings->number_of_cycles != -1)) break;
    do_sleep(settings);
    if(settings->verbose) {
      // write-flush so the dots appear per cycle
      fprintf(stderr, ".");
      fflush(stderr);
    }
  }
  if(settings->verbose) {
    // new line so we don't print on the same line as the dots
    fprintf(stderr, "\n");
  }
  // 0 (success) if met, 1 if unmet
  return ret == CONDITION_UNMET;
}
