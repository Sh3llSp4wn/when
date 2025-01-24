#ifndef WHEN_H
#define WHEN_H

#define DEFAULT_CYCLE_LENGTH 1

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

int when(settings_s *settings);

#endif
