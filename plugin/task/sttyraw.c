#include <stdio.h>
#include <stdlib.h>

int main()
{
  int charcode;
  
  system("stty raw");    /* 押したキーをそのままプログラムで扱う */
  //  system("stty -echo");  /* 押したキーを画面に出さない */
  
  charcode = 0;
  while(charcode != 13){
    printf("何か押してください: ");
    charcode = fgetc(stdin);
    printf("charcode=%3d", charcode);
    if (31 < charcode && charcode < 127) printf(" char='%c'", charcode);
    printf("\r\n");
  }
  
  /* 端末を普通の状態に戻す */
  system("stty echo");  /* キーを押してたら画面に出すようにする */
  system("stty -raw");  /* 押したキーをいったんバッファリングする */
  
  /* 正常終了 */
  return 0;
}
