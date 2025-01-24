/*
*
*
* This file implements a simple program for defering shell executin until 
* specified conditions are met
*
*
*/

// stdlib includes
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// internal includes
#include "file.h"

// global error string to set
const char *when_error = NULL;

void usage() {
  if (when_error) {
    fprintf(stderr, "\nERROR: %s\n\n", when_error);
  }
  fprintf(stderr, "when: [-vndez -s <int> -t <int> -c <int>] path\n"
         "\t-n: negate\n"
         "\t-d: watch for deletion\n"
         "\t-e: watch for creation\n"
         "\t-z: watch for filesize == 0\n"
         "\t-s <integer value>: watch for filesize > val\n"
         "\t-t <integer value>: stop after provided number of 'cycles'\n"
         "\t-c <integer value>: the ammount of time in seconds per 'cycle'\n"
         "\n\n'When' returns a status of 0 upon it's condition being met;\n"
         "> 0 on other conditions that indicate the privided\n"
         "conditions were not met (i.e. timeout); and < 0 on error.\n"
  );
  exit(-1);
}

typedef struct {
  int verbose;
  int negate;
  int w_del;
  int w_creat;
  int w_size;
  int w_zero;
  int cycle_length;
  int number_of_cycles;
  const char *path;
} settings_s;

extern int optind;
extern char* optarg;

int handle_arguments(settings_s *settings, int ac, char** av){
  char opt;
  int was_at_least_one_watch_set = 0;

  // validate that we got at least one opt
  if (ac == 1) {
    when_error = "NO ARGS";
    return 1;
  }

  // begin parsing command line flags
  while((opt = getopt(ac, av, "vndezs:t:c:")) != -1){
    switch(opt){
      case 'v':
        settings->verbose = 1;
        break;
      case 'n':
        settings->negate  = 1;
        break;
      case 'd':
        settings->w_del   = 1;
        break;
      case 'e':
        settings->w_creat = 1;
        break;
      case 'z':
        settings->w_zero  = 1;
        break;
      case 's':
        settings->w_size  = atoi(optarg);
        if(settings->w_size == 0) return 1;
        break;
      case 't':
        settings->number_of_cycles = atoi(optarg);
        if(settings->number_of_cycles == 0) return 1;
        break;
      case 'c':
        settings->cycle_length = atoi(optarg);
        if(settings->number_of_cycles == 0) return 1;
        break;
      default:
        return 1;
        break;
    }
  }
  // check if path was provided 
  // and collect it as an argument
  settings->path = av[optind];
  if(settings->path == NULL) {
    when_error = "NO PATH PROVIDED";
    return 1; 
  }

  was_at_least_one_watch_set =  settings->w_del;
  was_at_least_one_watch_set |= settings->w_creat;
  was_at_least_one_watch_set |= settings->w_size;
  was_at_least_one_watch_set |= settings->w_zero;
  if(!was_at_least_one_watch_set) {
    when_error = "NO WATCH SET (-dzse)";
    return 1;
  }

  return 0;
}

int main(int ac, char *av[]){
  // empty settings struct
  settings_s settings;

  // zeroize the settings object's fields
  memset(&settings, 0, sizeof(settings_s));

  // default settings incase they are not provided
  settings.cycle_length     = -1;  // default
  settings.number_of_cycles = -1;  // default

  if(handle_arguments(&settings, ac, av)){
    usage(); // exits negitave
  }
  return 0;
}
