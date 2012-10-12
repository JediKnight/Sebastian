#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

char gTgtDir[256];

int DotOmit(const struct dirent *pDe);
int TimeSort(const void *v1, const void *v2);


int main(int ac, char *av[])
{
  int             Cnt ;
  struct dirent   **pDe ;
  int             idx ;

  if (ac != 2) {
    fprintf(stderr, "Usage : %s TargetDir\n\n", av[0]);
    return  1 ;
  }
  strcpy(gTgtDir, av[1]);
  if (gTgtDir[strlen(gTgtDir)-1] != '/') {
    fprintf(stderr, "directoryの末尾に/を付けて下さい。\n\n");
    return  1 ;
 
 }

  Cnt = scandir(gTgtDir, &pDe, DotOmit, TimeSort);
  if (Cnt == -1) {
    perror("scandir ");
    return -1 ;
  }

  for (idx = 0 ; idx < Cnt ; idx++) {
    printf("No%4d : %s\n", idx+1, pDe[idx]->d_name);
    free(pDe[idx]);
  }

  free(pDe);
  return  0 ;
}

int dotOmit(const struct dirent *pDe)
{
  if (strcmp(pDe->d_name, "." ) &&    // "."でない
      strcmp(pDe->d_name, ".."))
    {    // かつ".."でもない
      return  1 ;
    }
  return  0 ;
}

int TimeSort(const void *v1, const void *v2)
{
  struct dirent   *d1, *d2 ;
  struct stat      s1,  s2 ;
  char            FNm[256];


  d1 = *(struct dirent **)v1 ;
  d2 = *(struct dirent **)v2 ;

  strcpy(FNm, gTgtDir);
  strcat(FNm, d1->d_name);
  stat  (FNm, &s1);

  strcpy(FNm, gTgtDir);
  strcat(FNm, d2->d_name);
  stat  (FNm, &s2);

  //  return (int)(s1.st_mtime - s2.st_mtime) ;   // 古い順の場合
  return (int)(s2.st_mtime - s1.st_mtime) ;   // 新しい順の場合
}
