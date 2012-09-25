#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DelSpace(a, b)							\
  char *p;								\
  strncpy(a, b, strlen(b));						\
  for (;(p = strstr(a, " ")) != NULL; memmove(a + strlen(a) - strlen(p), p + strlen(" "), strlen(p)))

#define BufferClear()				\
  while(getchar() != '\n')

#define DelReturn(a, b)				\
  a[b] = '\0'
