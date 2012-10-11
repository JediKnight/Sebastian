#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

void scan(char *path)
{
  DIR *dir;
  struct dirent *sdir;
  int i;
  if((dir = opendir(path)) == NULL)
    {
      printf("ディレクトリを開けませんでした\n");
      exit(EXIT_FAILURE);
    }
  for(i = 0; (sdir = readdir(dir)) != NULL; i++)
    {
      char type;
      switch(sdir->d_type)
	{
	case DT_FIFO:
	  type = 'f';
	  break;

	case DT_CHR:
	  type = 'c';
	  break;

	case DT_DIR:
	  type = 'd';
	  break;

	case DT_BLK:
	  type = 'b';
	  break;

	case DT_REG:
	  type = 'r';
	  break;

	case DT_LNK:
	  type = 'l';
	  break;

	case DT_SOCK:
	  type = 's';
	  break;

	case DT_WHT:
	  type = 'w';
	  break;

	case DT_UNKNOWN:
	default:
	  type = '?';
	  break;
	}

      printf("%c:%s\n", type, sdir->d_name);
    }
  closedir(dir);
}
