#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int dotOmit()
{
  return 1;
}

void scan(char *path)
{
  DIR *dir;
  struct dirent *sdir;
  struct stat st;
  int i, dnum;

  if((dnum = scandir(path, sdir, dotOmit, NULL)) < 0)
    {
      perror("scandir()");
      exit(EXIT_FAILURE);
    }

  for(i = 0; i < dnum; printf("%s\n", sdir->d_name), i++);
  closedir(dir);
}
